#pragma once

#include <windows.h>
#include "dxmain.h"

#include "Cube.h"
#include "Model.h"

class TestApp : public dxmain
{
public:
	TestApp(HINSTANCE hInstance);
	~TestApp();

	bool Init() override;
	bool Update(double dt) override;
	void Render(double dt) override;

private:
	Model bird_stand = Model();
	Model bird_body = Model();
	bool goingForward = false;
};

TestApp::TestApp(HINSTANCE hInstance) : dxmain(hInstance)
{

}

TestApp::~TestApp() 
{
	bird_stand.Release();
	bird_body.Release();
}

bool TestApp::Init()
{
	bool initSuccess = dxmain::Init();

	Utilities dxutils = Utilities();
	bird_stand.SetData(dxutils.LoadModel("models/bird_stand.obj"));
	bird_body.SetData(dxutils.LoadModel("models/bird_main.obj"));

	bird_stand.Create();
	bird_body.Create();

	bird_stand.SetPosition(XMFLOAT3(0.0f, -3.0f, 0.0f));
	bird_stand.SetRotation(XMFLOAT3(0.0f, -1.0f, 0.0f));

	return initSuccess;
}

bool TestApp::Update(double dt)
{
	if (bird_body.GetRotation().z > 2.0f) {
		goingForward = false;
	}
	if (bird_body.GetRotation().z < -0.8f) {
		goingForward = true;
	}

	if (goingForward)
	{
		bird_body.SetRotation(XMFLOAT3(0.0f, -1.0f, bird_body.GetRotation().z+dt));
	}
	else
	{
		bird_body.SetRotation(XMFLOAT3(0.0f, -1.0f, bird_body.GetRotation().z-dt));
	}

	OutputDebugString(std::to_string(bird_body.GetRotation().z).c_str());
	OutputDebugString("\n");

	bird_stand.Update(dt);
	bird_body.Update(dt);

	return true;
}

void TestApp::Render(double dt)
{
	//Clear back buffer & depth stencil view
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);
	m_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//Render models
	bird_stand.Render(dt);
	bird_body.Render(dt);

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

