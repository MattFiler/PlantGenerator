#include "TestScene.h"

/* Init the objects in the scene */
void TestScene::Init()
{
	Utilities dxutils = Utilities();

	main_cam = Camera();
	bird_stand = Model();
	bird_body = Model();
	light_source = Light();

	doAnimation = true;
	goingForward = false;

	bird_stand.SetData(dxutils.LoadModel("models/bird_stand.obj"));
	bird_body.SetData(dxutils.LoadModel("models/bird_main.obj"));

	GameObjectManager::AddObject(&bird_stand);
	GameObjectManager::AddObject(&bird_body);
	GameObjectManager::AddObject(&main_cam);
	GameObjectManager::AddObject(&light_source);
	GameObjectManager::Create();

	bird_stand.SetPosition(XMFLOAT3(0.0f, -3.0f, 0.0f));
	bird_stand.SetRotation(XMFLOAT3(0.0f, -1.0f, 0.0f));

	main_cam.SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, 4.1f));

	light_source.SetColour(XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f));
	light_source.SetPosition(DirectX::XMFLOAT3(5.0f, 0.0f, -4.1f));
}

/* Release the objects in the scene */
void TestScene::Release()
{
	GameObjectManager::Release();
}

/* Update the objects in the scene */
bool TestScene::Update(double dt)
{
	XMFLOAT3 lightPos = light_source.GetPosition();
	ImGui::Begin("TestScene Control");
	ImGui::Checkbox("Do Animation", &doAnimation);
	ImGui::SliderFloat("Light X", &lightPos.x, -20.0f, 20.0f);
	ImGui::SliderFloat("Light Y", &lightPos.y, -20.0f, 20.0f);
	ImGui::SliderFloat("Light Z", &lightPos.z, -20.0f, 20.0f);
	ImGui::End();
	light_source.SetPosition(lightPos);

	if (doAnimation) 
	{
		if (bird_body.GetRotation().z > 2.0f) {
			goingForward = false;
		}
		if (bird_body.GetRotation().z < -0.8f) {
			goingForward = true;
		}

		if (goingForward)
		{
			bird_body.SetRotation(XMFLOAT3(0.0f, -1.0f, bird_body.GetRotation().z + dt));
		}
		else
		{
			bird_body.SetRotation(XMFLOAT3(0.0f, -1.0f, bird_body.GetRotation().z - dt));
		}
	}

	GameObjectManager::Update(dt);

	return true;
}

/* Render the objects in the scene */
void TestScene::Render(double dt)
{
	GameObjectManager::Render(dt);
}
