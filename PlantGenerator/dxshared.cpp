#include "dxshared.h"

/* Init shared values */
ID3D11Device* dxshared::m_pDevice = nullptr;
ID3D11DeviceContext* dxshared::m_pImmediateContext = nullptr;
ID3D11VertexShader* dxshared::m_vertexShader = nullptr;
ID3D11PixelShader* dxshared::m_pixelShader = nullptr;
UINT dxshared::m_renderWidth = 0;
UINT dxshared::m_renderHeight = 0;
int dxshared::renderIndexCount = 0;

/* Set the shared device */
void dxshared::SetDevice(ID3D11Device * device)
{
	m_pDevice = device;
}

/* Get the shared device, warn if null */
ID3D11Device * dxshared::GetDevice()
{
	if (!m_pDevice) 
	{
		OutputDebugString("Tried to get device, but it was null!!");
	}
	return m_pDevice;
}

/* Set the shared device context */
void dxshared::SetDeviceContext(ID3D11DeviceContext * deviceContext)
{
	m_pImmediateContext = deviceContext;
}

/* Get the shared device context, warn if null */
ID3D11DeviceContext * dxshared::GetDeviceContext()
{
	if (!m_pImmediateContext)
	{
		OutputDebugString("Tried to get device context, but it was null!!");
	}
	return m_pImmediateContext;
}

/* Set the vertex shader */
void dxshared::SetVertexShader(ID3D11VertexShader * vertexShader)
{
	m_vertexShader = vertexShader;
}

/* Get the vertex shader */
ID3D11VertexShader * dxshared::GetVertexShader()
{
	if (!m_vertexShader)
	{
		OutputDebugString("Tried to get vertex shader, but it was null!!");
	}
	return m_vertexShader;
}

/* Set the pixel shader */
void dxshared::SetPixelShader(ID3D11PixelShader * pixelShader)
{
	m_pixelShader = pixelShader;
}

/* Get the pixel shader */
ID3D11PixelShader * dxshared::GetPixelShader()
{
	if (!m_pixelShader)
	{
		OutputDebugString("Tried to get pixel shader, but it was null!!");
	}
	return m_pixelShader;
}

/* Set the render width */
void dxshared::SetWidth(UINT width)
{
	m_renderWidth = width;
}

/* Get the render width */
UINT dxshared::GetWidth()
{
	if (m_renderWidth == 0)
	{
		OutputDebugString("Tried to get render width, but it was null!!");
	}
	return m_renderWidth;
}

/* Set the render height */
void dxshared::SetHeight(UINT height)
{
	m_renderHeight = height;
}

/* Get the render height */
UINT dxshared::GetHeight()
{
	if (m_renderHeight == 0)
	{
		OutputDebugString("Tried to get render height, but it was null!!");
	}
	return m_renderHeight;
}
