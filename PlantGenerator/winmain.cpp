#pragma once

#include <windows.h>
#include "dxmain.h"

#include "Cube.h"

class TestApp : public dxmain
{
public:
	TestApp(HINSTANCE hInstance);
	~TestApp();

	bool Init() override;
	bool Update(float dt) override;
	void Render(float dt) override;

private:
	Cube a_cube = Cube();
};

TestApp::TestApp(HINSTANCE hInstance) : dxmain(hInstance)
{

}

TestApp::~TestApp() 
{
	a_cube.Release();
}

bool TestApp::Init()
{
	bool initSuccess = dxmain::Init();
	a_cube.Create();
	return initSuccess;
}

bool TestApp::Update(float dt)
{
	return false;
}

void TestApp::Render(float dt)
{
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);

	a_cube.Render();

	m_pSwapChain->Present(0, 0);
}

/* Entry point */
int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	//MessageBox(NULL, "Hello world", "Test", 0);

	TestApp tApp(hInstance);
	if (!tApp.Init()) 
	{
		return 1;
	}

	return tApp.Run();
}

