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
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 8;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	HRESULT hr = dxshared::GetDevice()->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	//Set vertex buffer 
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	dxshared::GetDeviceContext()->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

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
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 36;        //36 vertices needed for 12 triangles in a triangle list 
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	hr = dxshared::GetDevice()->CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
	if (FAILED(hr))
	{
		OutputDebugString("Failed to create index buffer!!");
		return false;
	}

	//Set index buffer 
	dxshared::GetDeviceContext()->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	//Create the constant buffer 
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = dxshared::GetDevice()->CreateBuffer(&bd, nullptr, &g_pConstantBuffer);
	if (FAILED(hr))
	{
		OutputDebugString("Failed to create the constant buffer!!");
		return false;
	}

	//Initialize the world matrix 
	m_cBufferObj.mWorld = XMMatrixIdentity();

	//Initialize the view matrix 
	XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_cBufferObj.mView = XMMatrixLookAtLH(Eye, At, Up);

	//Initialize the projection matrix 
	m_cBufferObj.mProjection = XMMatrixPerspectiveFovLH(XM_PIDIV2, dxshared::GetWidth() / (FLOAT)dxshared::GetHeight(), 0.01f, 100.0f);
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

/* Render the cube */
bool Cube::Render()
{
	//Update variables
	ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(m_cBufferObj.mWorld);
	cb.mView = XMMatrixTranspose(m_cBufferObj.mView);
	cb.mProjection = XMMatrixTranspose(m_cBufferObj.mProjection);
	dxshared::GetDeviceContext()->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb, 0, 0);

	//Draw
	dxshared::GetDeviceContext()->VSSetShader(dxshared::GetVertexShader(), nullptr, 0);
	dxshared::GetDeviceContext()->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	dxshared::GetDeviceContext()->PSSetShader(dxshared::GetPixelShader(), nullptr, 0);
	dxshared::GetDeviceContext()->DrawIndexed(36, 0, 0);        //36 vertices needed for 12 triangles in a triangle list 
	return true;
}
