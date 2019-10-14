#include "Cube.h"

using namespace DirectX;

/* Create the cube */
bool Cube::Create()
{
	GameObject::Create();

	//Create vertex buffer 
	SimpleVertex vertices[] =
	{
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
	};
	vertexCount = ARRAYSIZE(vertices);
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * vertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	HRESULT hr = dxshared::m_pDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	//Create index buffer 
	WORD indices[] =
	{
		3,1,0,
		2,1,3,

		0,5,4,
		1,5,0,

		3,4,7,
		0,4,3,

		1,6,5,
		2,6,1,

		2,7,6,
		3,7,2,

		6,4,5,
		7,4,6,
	};
	indexCount = ARRAYSIZE(indices);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * indexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	hr = dxshared::m_pDevice->CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
	if (FAILED(hr))
	{
		OutputDebugString("Failed to create index buffer!!");
		return false;
	}

	//Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	Utilities dxutils = Utilities();
	hr = dxutils.CompileShaderFromFile(L"cube.fx", "VS", "vs_4_0", &pVSBlob);
	if (FAILED(hr))
	{
		OutputDebugString("The FX file cannot be compiled!!");
		return false;
	}

	//Create the vertex shader
	hr = dxshared::m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_vertexShader);
	if (FAILED(hr))
	{
		OutputDebugString("Failed to create vertex shader!!");
		pVSBlob->Release();
		return false;
	}

	//Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	//Create the input layout
	hr = dxshared::m_pDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_vertexLayout);
	pVSBlob->Release();
	if (FAILED(hr))
	{
		return false;
	}

	//Set the input layout
	dxshared::m_pImmediateContext->IASetInputLayout(m_vertexLayout);

	//Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = dxutils.CompileShaderFromFile(L"cube.fx", "PS", "ps_4_0", &pPSBlob);
	if (FAILED(hr))
	{
		OutputDebugString("The FX file cannot be compiled!!");
		return false;
	}

	//Create the pixel shader
	hr = dxshared::m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pixelShader);
	pPSBlob->Release();
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

/* Release the cube */
bool Cube::Release()
{
	GameObject::Release();

	Memory::SafeRelease(g_pVertexBuffer);
	Memory::SafeRelease(g_pIndexBuffer);
	return true;
}

/* Update the cube */
bool Cube::Update(float dt)
{
	GameObject::Update(dt);

	return true;
}

/* Render the cube */
bool Cube::Render(float dt)
{
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

	//Draw
	dxshared::m_pImmediateContext->DrawIndexed(indexCount, 0, 0);

	return true;
}
