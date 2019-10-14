#pragma once

#include <windows.h>
#include "dxmain.h"

#include "PointLight.h"
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
	Cube a_cube2 = Cube();
	PointLight a_light = PointLight();
};

TestApp::TestApp(HINSTANCE hInstance) : dxmain(hInstance)
{

}

TestApp::~TestApp() 
{
	a_cube.Release();
	a_cube2.Release();
}

bool TestApp::Init()
{
	bool initSuccess = dxmain::Init();

	//Create both cubes
	a_cube.Create();
	a_cube2.Create();

	//Create a light and assign to both cubes
	a_light.Create();
	a_cube.UseLight(&a_light);
	a_cube2.UseLight(&a_light);

	//Set pos of cube 2
	a_cube2.SetPosition(DirectX::XMFLOAT3(0.0f, 3.0f, 0.0f));

	return initSuccess;
}

bool TestApp::Update(float dt)
{
	//Over time, rotate both cubes in alt directions
	a_cube.SetRotation(DirectX::XMFLOAT3(0.0f, dt, 0.0f));
	a_cube2.SetRotation(DirectX::XMFLOAT3(0.0f, -dt, 0.0f));

	//Update both cubes
	a_cube.Update(dt);
	a_cube2.Update(dt);

	a_light.Update(dt);

	return true;
}

void TestApp::Render(float dt)
{
	//Clear back buffer & depth stencil view
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);
	m_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//Render both cubes
	a_cube.Render(dt);
	a_cube2.Render(dt);

	a_light.Render(dt);

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

