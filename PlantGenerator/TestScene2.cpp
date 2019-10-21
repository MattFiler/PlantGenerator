#include "TestScene2.h"

/* Init the objects in the scene */
void TestScene2::Init()
{
	Utilities dxutils = Utilities();

	main_cam = Camera();
	cube_model = Model();
	light_source = Light();

	cube_model.SetData(dxutils.LoadModel("models/cube.obj"));

	GameObjectManager::AddObject(&cube_model);
	GameObjectManager::AddObject(&light_source);
	GameObjectManager::AddObject(&main_cam);
	GameObjectManager::Create();

	main_cam.SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, 4.1f));

	light_source.SetColour(XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f));
	light_source.SetPosition(DirectX::XMFLOAT3(5.0f, 0.0f, -4.1f));
}

/* Release the objects in the scene */
void TestScene2::Release()
{
	GameObjectManager::Release();
}

/* Update the objects in the scene */
bool TestScene2::Update(double dt)
{
	XMFLOAT3 lightPos = light_source.GetPosition();
	ImGui::Begin("TestScene2 Control");
	ImGui::SliderFloat("Light X", &lightPos.x, -20.0f, 20.0f);
	ImGui::SliderFloat("Light Y", &lightPos.y, -20.0f, 20.0f);
	ImGui::SliderFloat("Light Z", &lightPos.z, -20.0f, 20.0f);
	ImGui::End();
	light_source.SetPosition(lightPos);

	GameObjectManager::Update(dt);

	return true;
}

/* Render the objects in the scene */
void TestScene2::Render(double dt)
{
	GameObjectManager::Render(dt);
}
