#include "TestScene.h"

/* Init the objects in the scene */
void TestScene::Init()
{
	main_cam = Camera();
	GameObjectManager::AddObject(&main_cam);
	GameObjectManager::Create();
	main_cam.SetLocked(true);
}

/* Release the objects in the scene */
void TestScene::Release()
{
	GameObjectManager::Release();
}

/* Update the objects in the scene */
bool TestScene::Update(double dt)
{
	bool open = true;
	ImGui::SetNextWindowPos(ImVec2(950, 0));
	ImGui::SetNextWindowSize(ImVec2(330, 720));
	ImGui::Begin("Controls", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::End();

	GameObjectManager::Update(dt);

	return true;
}

/* Render the objects in the scene */
void TestScene::Render(double dt)
{
	GameObjectManager::Render(dt);
}
