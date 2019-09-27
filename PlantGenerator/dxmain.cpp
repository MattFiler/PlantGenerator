#include "dxmain.h"

/* Because we can't create this function as a callback in dxmain, here's a wrapper for it in global namespace */
namespace {
	dxmain* g_pApp = nullptr;
}
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	if (g_pApp) 
	{
		return g_pApp->MsgProc(hwnd, msg, wParam, lParam);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

/* Initialise the default window configuration */
dxmain::dxmain(HINSTANCE hInstance)
{
	m_hAppInstance = hInstance;
	m_hAppWnd = NULL;
	m_clientWidth = 800;
	m_clientHeight = 600; //todo: alt sizes
	m_appTitle = "Plant Generator";
	m_wndStyle = WS_OVERLAPPEDWINDOW; //todo: do we want this style?

	g_pApp = this;
}

/* Keep an eye on Windows messages, and call Update/Render if we aren't told to exit */
int dxmain::Run()
{
	MSG msg = { 0 };
	while (WM_QUIT != msg.message) 
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update(0.0f); //todo - calculate delta time
			Render(0.0f);
		}
	}
	return static_cast<int>(msg.wParam);
}

/* Set appropriate properties and then initialise window */
bool dxmain::Init()
{
	//Setup window class
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = m_hAppInstance;
	wcex.lpfnWndProc = MainWndProc; //The global namespace wrapper (above)
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); //todo: set the window icon here as imported
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); //todo: custom cursor?
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "dxmain";

	if (!RegisterClassEx(&wcex)) 
	{
		OutputDebugString("Failed to setup window class in dxmain!!");
		return false;
	}

	//Adjust window size for no menu bar
	RECT r = { 0, 0, m_clientWidth, m_clientHeight };
	AdjustWindowRect(&r, m_wndStyle, FALSE);

	//Get metrics for window
	UINT width = r.right - r.left;
	UINT height = r.bottom - r.top;
	UINT xPos = (GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
	UINT yPos = (GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);

	//Create window
	m_hAppWnd = CreateWindow("dxmain", m_appTitle.c_str(), m_wndStyle, xPos, yPos, width, height, NULL, NULL, m_hAppInstance, NULL);

	if (!m_hAppWnd)
	{
		OutputDebugString("Failed to create window in dxmain!!");
		return false;
	}

	//Show window
	ShowWindow(m_hAppWnd, SW_SHOW);
	return true;
}

/* Handle windows messages */
LRESULT dxmain::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}