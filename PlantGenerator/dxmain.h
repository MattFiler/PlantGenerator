#pragma once

#include "dxutils.h";
#include <string>

class dxmain
{
public:
	dxmain(HINSTANCE hInstance);
	virtual ~dxmain();

	int Run();

	virtual bool Init();
	virtual bool Update(float dt) = 0;
	virtual void Render(float dt) = 0;
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	//Window
	bool InitWindow();
	HWND m_hAppWnd;
	HINSTANCE m_hAppInstance;
	UINT m_clientWidth;
	UINT m_clientHeight;
	std::string m_appTitle;
	DWORD m_wndStyle;

	//DirectX
	bool InitDirectX();
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pImmediateContext;
	IDXGISwapChain* m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11Texture2D* g_pDepthStencil = nullptr;
	ID3D11DepthStencilView* g_pDepthStencilView = nullptr;
	D3D_DRIVER_TYPE m_driverType;
	D3D_FEATURE_LEVEL m_featureLevel;
	D3D11_VIEWPORT m_viewport;
	ID3D11RasterizerState* WireFrame;
};

