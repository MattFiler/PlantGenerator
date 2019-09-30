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

	m_pDevice = nullptr;
	m_pImmediateContext = nullptr;
	m_pRenderTargetView = nullptr;
	m_pSwapChain = nullptr;
	m_vertexShader = nullptr;
	m_pixelShader = nullptr;
	m_vertexLayout = nullptr;
}

/* Release our d3d resources on exit */
dxmain::~dxmain()
{
	if (m_pImmediateContext)
	{
		m_pImmediateContext->ClearState();
	}
	Memory::SafeRelease(m_pRenderTargetView);
	Memory::SafeRelease(m_pSwapChain);
	Memory::SafeRelease(m_pImmediateContext);
	Memory::SafeRelease(m_pDevice);
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
	return InitWindow() && InitDirectX();
}

/* Set appropriate properties and then initialise window */
bool dxmain::InitWindow()
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

/* Set appropriate properties and then initialise d3d to the window */
bool dxmain::InitDirectX()
{
	//Request d3d debugging if in debug
	UINT createDeviceFlags = 0;
#if _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	//Supported driver types (in order of priority)
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	//Supported d3d feature levels
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	//Create & further setup swapchain class
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	//Buffering
	swapDesc.BufferCount = 1; //Double buffered

	//Buffer size and format
	swapDesc.BufferDesc.Width = m_clientWidth;
	swapDesc.BufferDesc.Height = m_clientHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //32-bit unsigned normal

	//Target FPS
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;

	//Output to our window
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = m_hAppWnd;
	swapDesc.Windowed = true; //Start as windowed
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //Allow alt+enter fullscreen (doesn't resize buffer)

	//Operation
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //Most efficient

	//Multisampling
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	//Try create the d3d device and swap chain
	HRESULT result;
	for (int i = 0; i < numDriverTypes; i++) 
	{
		result = D3D11CreateDeviceAndSwapChain(NULL, driverTypes[i], NULL, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &swapDesc, &m_pSwapChain, &m_pDevice, &m_featureLevel, &m_pImmediateContext);
		if (SUCCEEDED(result)) 
		{
			m_driverType = driverTypes[i];
			break;
		}
	}

	if (FAILED(result)) 
	{
		OutputDebugString("Failed to create device and/or swap chain!!");
		return false;
	}

	//Create the render target view
	ID3D11Texture2D* m_pBackBufferTex = NULL;
	HR(m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_pBackBufferTex)));
	HR(m_pDevice->CreateRenderTargetView(m_pBackBufferTex, nullptr, &m_pRenderTargetView));
	Memory::SafeRelease(m_pBackBufferTex);

	//Bind the render target view
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr); //no depth stencil view (yet)

	//Create the viewport
	m_viewport.Width = static_cast<float>(m_clientWidth);
	m_viewport.Height = static_cast<float>(m_clientHeight);
	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;

	//Bind the viewport
	m_pImmediateContext->RSSetViewports(1, &m_viewport);

	//Share out render size (todo: will need to be done on update for resizing)
	dxshared::SetWidth(m_clientWidth);
	dxshared::SetHeight(m_clientHeight);
	
	//Share out the device and device context
	dxshared::SetDevice(m_pDevice);
	dxshared::SetDeviceContext(m_pImmediateContext);
	
	//Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	Utilities dxutils = Utilities();
	result = dxutils.CompileShaderFromFile(L"cube.fx", "VS", "vs_4_0", &pVSBlob);
	if (FAILED(result))
	{
		OutputDebugString("The FX file cannot be compiled!!");
		return false;
	}

	//Create the vertex shader
	result = m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_vertexShader);
	if (FAILED(result))
	{
		OutputDebugString("Failed to create vertex shader!!");
		pVSBlob->Release();
		return false;
	}
	dxshared::SetVertexShader(m_vertexShader);

	//Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	//Create the input layout
	result = m_pDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_vertexLayout);
	pVSBlob->Release();
	if (FAILED(result))
	{
		return false;
	}

	//Set the input layout
	m_pImmediateContext->IASetInputLayout(m_vertexLayout);

	//Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	result = dxutils.CompileShaderFromFile(L"cube.fx", "PS", "ps_4_0", &pPSBlob);
	if (FAILED(result))
	{
		OutputDebugString("The FX file cannot be compiled!!");
		return false;
	}

	//Create the pixel shader
	result = m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pixelShader);
	pPSBlob->Release();
	if (FAILED(result))
	{
		return false;
	}
	dxshared::SetPixelShader(m_pixelShader);

	//Set topology for rendering
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
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