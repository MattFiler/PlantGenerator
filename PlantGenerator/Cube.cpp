#include "Cube.h"

using namespace DirectX;

/* Create the cube */
bool Cube::Create()
{
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

	//Create the constant buffer 
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = dxshared::m_pDevice->CreateBuffer(&bd, nullptr, &g_pConstantBuffer);
	if (FAILED(hr))
	{
		OutputDebugString("Failed to create the constant buffer!!");
		return false;
	}

	//Initialize the world matrix 
	mWorld = XMMatrixIdentity();
	return true;
}

/* Release the cube */
bool Cube::Release()
{
	Memory::SafeRelease(g_pVertexBuffer);
	Memory::SafeRelease(g_pIndexBuffer);
	Memory::SafeRelease(g_pConstantBuffer);
	return true;
}

/* Update the cube */
bool Cube::Update(float dt)
{
	//Set the cube's world based on translations (todo: X rotation)
	mWorld = XMMatrixScaling(scale.x, scale.y, scale.z) * XMMatrixRotationZ(rotation.z) * XMMatrixTranslation(position.x, position.y, position.z) * XMMatrixRotationY(rotation.y);

	return true;
}

/* Set the cube's position */
void Cube::SetPosition(Vector3 _pos)
{
	position = _pos;
}

/* Set the cube's rotation */
void Cube::SetRotation(Vector3 _rot)
{
	rotation = _rot;
}

/* Set the cube's scale */
void Cube::SetScale(Vector3 _scale)
{
	scale = _scale;
}

/* Render the cube */
bool Cube::Render(float dt)
{
	//Update variables
	ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(mWorld);
	cb.mView = XMMatrixTranspose(dxshared::mView);
	cb.mProjection = XMMatrixTranspose(dxshared::mProjection);
	dxshared::m_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb, 0, 0);

	//Set index buffer 
	dxshared::m_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	//Set vertex buffer 
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	dxshared::m_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	//Draw
	dxshared::m_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	dxshared::m_pImmediateContext->DrawIndexed(indexCount, 0, 0);

	return true;
}
