#include "GameObject.h"

/* Create our low level GameObject resources */
void GameObject::Create()
{
	//Initialize the world matrix 
	mWorld = XMMatrixIdentity();

#ifdef _DEBUG
	//Create vertex buffer
	SimpleVertexAlt vertices[] =
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
	GO_VertCount = ARRAYSIZE(vertices);
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertexAlt) * GO_VertCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	HR(dxshared::m_pDevice->CreateBuffer(&bd, &InitData, &GO_VertexBuffer));

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
	GO_IndexCount = ARRAYSIZE(indices);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * GO_IndexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	HR(dxshared::m_pDevice->CreateBuffer(&bd, &InitData, &GO_IndexBuffer));

	//Constant buffer 
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBufferAlt);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	HR(dxshared::m_pDevice->CreateBuffer(&bd, nullptr, &GO_ConstantBuffer));

	//Vertex shader
	ID3DBlob* pVSBlob = nullptr;
	Utilities dxutils = Utilities();
	HR(dxutils.CompileShaderFromFile(L"ObjectShaderDebug.fx", "VSDebug", "vs_4_0", &pVSBlob));
	HR(dxshared::m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &GO_VertexShader));

	//Input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	HR(dxshared::m_pDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &GO_VertLayout));
	pVSBlob->Release();

	//Pixel shader
	ID3DBlob* pPSBlob = nullptr;
	HR(dxutils.CompileShaderFromFile(L"ObjectShaderDebug.fx", "PSDebug", "ps_4_0", &pPSBlob));
	HR(dxshared::m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &GO_PixelShader));
	pPSBlob->Release();
#endif
}

/* Safely release our low level GameObject memory */
void GameObject::Release()
{
#ifdef _DEBUG
	Memory::SafeRelease(GO_VertexBuffer);
	Memory::SafeRelease(GO_IndexBuffer);
	Memory::SafeRelease(GO_VertexShader);
	Memory::SafeRelease(GO_PixelShader);
	Memory::SafeRelease(GO_ConstantBuffer);
#endif
}

/* Perform low level GameObject update functions */
void GameObject::Update(float dt)
{
	if (!isActive) return;
	mWorld = XMMatrixScaling(scale.x, scale.y, scale.z) * XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) * XMMatrixTranslation(position.x, position.y, position.z);
}

/* Perform low level GameObject render functions */
void GameObject::Render(float dt)
{
	if (!isActive) return;
	if (isInvisible) return;
#ifdef _DEBUG
	if (dxshared::enableDebug) {
		//Input layout
		dxshared::m_pImmediateContext->IASetInputLayout(GO_VertLayout);

		//Shaders
		dxshared::m_pImmediateContext->VSSetShader(GO_VertexShader, nullptr, 0);
		dxshared::m_pImmediateContext->PSSetShader(GO_PixelShader, nullptr, 0);

		//Constant buffer
		ConstantBufferAlt cb;
		cb.mWorld = XMMatrixTranspose(mWorld);
		cb.mView = XMMatrixTranspose(dxshared::mView);
		cb.mProjection = XMMatrixTranspose(dxshared::mProjection);
		dxshared::m_pImmediateContext->UpdateSubresource(GO_ConstantBuffer, 0, nullptr, &cb, 0, 0);
		dxshared::m_pImmediateContext->VSSetConstantBuffers(0, 1, &GO_ConstantBuffer);
		dxshared::m_pImmediateContext->PSSetConstantBuffers(0, 1, &GO_ConstantBuffer);

		//Index/vertex buffers
		dxshared::m_pImmediateContext->IASetIndexBuffer(GO_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
		UINT stride = sizeof(SimpleVertexAlt);
		UINT offset = 0;
		dxshared::m_pImmediateContext->IASetVertexBuffers(0, 1, &GO_VertexBuffer, &stride, &offset);

		//Draw
		dxshared::m_pImmediateContext->DrawIndexed(GO_IndexCount, 0, 0);
	}
#endif
}