#pragma once

#include <windows.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <DirectXMath.h>

struct dxshared 
{
public:
	static ID3D11Device* m_pDevice;
	static ID3D11DeviceContext* m_pImmediateContext;

	static UINT m_renderWidth;
	static UINT m_renderHeight;

	static DirectX::XMMATRIX mView;
	static DirectX::XMMATRIX mProjection;

	static DirectX::XMFLOAT4 ambientLightColour;

	static bool enableDebug;
};