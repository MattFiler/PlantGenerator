#pragma once
#define WIN32_LEAN_AND_MEAN //Tidy the windows.h libraries for the basics we need
#include <windows.h>
#include <string>

class dxmain
{
public:
	dxmain(HINSTANCE hInstance);
	virtual ~dxmain() = default;

	int Run();

	virtual bool Init();
	virtual bool Update(float dt) = 0;
	virtual void Render(float dt) = 0;
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	HWND m_hAppWnd;
	HINSTANCE m_hAppInstance;
	UINT m_clientWidth;
	UINT m_clientHeight;
	std::string m_appTitle;
	DWORD m_wndStyle;
};

