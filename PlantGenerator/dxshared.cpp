#include "dxshared.h"

/* Init shared values to null */
ID3D11Device* dxshared::m_pDevice = nullptr;
ID3D11DeviceContext* dxshared::m_pImmediateContext = nullptr;

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
