#include "triangle.h"

/* Create the triangle */
bool Triangle::Create()
{
	//Create vertex buffer
	SimpleVertex vertices[] =
	{
		DirectX::XMFLOAT3(0.0f, 0.5f, 0.5f),
		DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f),
		DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f),
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 3;
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
	return true;
}

/* Release the triangle */
bool Triangle::Release()
{
	Memory::SafeRelease(g_pVertexBuffer);
	return true;
}

/* Render the triangle */
bool Triangle::Render()
{
	dxshared::GetDeviceContext()->VSSetShader(dxshared::GetVertexShader(), nullptr, 0);
	dxshared::GetDeviceContext()->PSSetShader(dxshared::GetPixelShader(), nullptr, 0);
	dxshared::GetDeviceContext()->Draw(3, 0);
	return true;
}
