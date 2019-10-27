#include "SceneManager.h"
#include "Scene.h"

/* Destroy active scene on exit, if one is */
SceneManager::~SceneManager()
{
	if (currentSceneIndex != -1)
		availableScenes[currentSceneIndex]->Release();
}

bool SceneManager::Init()
{
	bool dxInit = dxmain::Init();

	AddScene(&newScene);
	AddScene(&newScene2);
	AddScene(&newScene3);
	ChangeScene(0);

	return dxInit;
}

/* Update the current scene, and handle swapping of scenes */
bool SceneManager::Update(double dt)
{
	//Swap scenes if requested
	if (requestedSceneIndex != currentSceneIndex)
	{
		if (currentSceneIndex != -1)
			availableScenes[currentSceneIndex]->Release();
		currentSceneIndex = requestedSceneIndex;
		availableScenes[currentSceneIndex]->Init();
	}

	//New ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//Scene manager ImGui control
	ImGui::Begin("Editor");
	if (ImGui::Button("Flower Generator"))
	{
		ChangeScene(2);
	}
	ImGui::End();
	
	//Update current scene
	if (currentSceneIndex != -1)
		return availableScenes[currentSceneIndex]->Update(dt);
}

/* Render the current scene (if one is set) */
void SceneManager::Render(double dt)
{
	//Clear back buffer & depth stencil view
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);
	m_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//Render scene
	if (currentSceneIndex != -1)
		availableScenes[currentSceneIndex]->Render(dt);

	//Render ImGui
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	//Present the back buffer to front buffer
	m_pSwapChain->Present(0, 0);
}
