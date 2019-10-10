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
	a_cube.Update(dt);
	return true;
}

void TestApp::Render(float dt)
{
	//Clear back buffer & depth stencil view
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);
	m_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//Reset shared index counts before rendering anything
	dxshared::renderIndexCount = 0;
	dxshared::renderVertexCount = 0;

	//Set global shader to use (might change this to object specific down the line (will need to remove the shader compiler code from dxmain to each class))
	dxshared::m_pImmediateContext->VSSetShader(m_vertexShader, nullptr, 0);
	dxshared::m_pImmediateContext->PSSetShader(m_pixelShader, nullptr, 0);

	//Render objects
	a_cube.Render(dt);

	//Present the back buffer to front buffer
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

