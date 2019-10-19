#include "Model.h"
#include <fstream>
#include <vector>

/* Create basic resources */
void Model::Create()
{
	GameObject::Create();

	//Create vertex buffer 
	vertexCount = modelMetaData.compVertices.size();
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * vertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = modelMetaData.compVertices.data();
	HR(dxshared::m_pDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer));

	//Create index buffer 
	indexCount = modelMetaData.compIndices.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * indexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = modelMetaData.compIndices.data();
	HR(dxshared::m_pDevice->CreateBuffer(&bd, &InitData, &g_pIndexBuffer));

	//Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	Utilities dxutils = Utilities();
	HR(dxutils.CompileShaderFromFile(L"cube.fx", "VS", "vs_4_0", &pVSBlob));

	//Create the vertex shader
	HR(dxshared::m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_vertexShader));

	//Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	//Create the input layout
	HR(dxshared::m_pDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_vertexLayout));
	pVSBlob->Release();

	//Set the input layout
	dxshared::m_pImmediateContext->IASetInputLayout(m_vertexLayout);

	//Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	HR(dxutils.CompileShaderFromFile(L"cube.fx", "PS", "ps_4_0", &pPSBlob));

	//Create the pixel shader
	HR(dxshared::m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pixelShader));
	pPSBlob->Release();

	//Load the texture
	std::wstring widestr = std::wstring(modelMetaData.textureName.begin(), modelMetaData.textureName.end());
	HR(CreateDDSTextureFromFile(dxshared::m_pDevice, widestr.c_str(), nullptr, &g_pTextureRV));
	
	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(dxshared::m_pDevice->CreateSamplerState(&sampDesc, &g_pSamplerLinear));
}

/* Release the model */
void Model::Release()
{
	GameObject::Release();

	Memory::SafeRelease(g_pVertexBuffer);
	Memory::SafeRelease(g_pIndexBuffer);
	Memory::SafeRelease(m_vertexShader);
	Memory::SafeRelease(m_pixelShader);
	Memory::SafeRelease(g_pTextureRV);
}

/* Update the model */
void Model::Update(float dt)
{
	if (vertexCount == 0 && indexCount == 0) return;

	GameObject::Update(dt);
}

/* Render the model */
void Model::Render(float dt)
{
	if (vertexCount == 0 && indexCount == 0) return;
	if (!isActive) return;

	GameObject::Render(dt);

	//Set shaders to use
	dxshared::m_pImmediateContext->VSSetShader(m_vertexShader, nullptr, 0);
	dxshared::m_pImmediateContext->PSSetShader(m_pixelShader, nullptr, 0);

	//Set index buffer 
	dxshared::m_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	//Set vertex buffer 
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	dxshared::m_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	//Set texture and sampler
	dxshared::m_pImmediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);
	dxshared::m_pImmediateContext->PSSetSamplers(0, 1, &g_pSamplerLinear);

	//Draw
	dxshared::m_pImmediateContext->DrawIndexed(indexCount, 0, 0);
}
