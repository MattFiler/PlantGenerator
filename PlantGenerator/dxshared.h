#pragma once

#include <windows.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

struct dxshared 
{
public:
	static void SetDevice(ID3D11Device* device);
	static ID3D11Device* GetDevice();

	static void SetDeviceContext(ID3D11DeviceContext* deviceContext);
	static ID3D11DeviceContext* GetDeviceContext();

private:
	static ID3D11Device* m_pDevice;
	static ID3D11DeviceContext* m_pImmediateContext;
};