#include "TestScene.h"

/* Init the objects in the scene */
void TestScene::Init()
{
	Utilities dxutils = Utilities();

	main_cam.Create();
	main_cam.SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, 4.1f));

	bird_stand.SetData(dxutils.LoadModel("models/bird_stand.obj"));
	bird_stand.Create();
	bird_stand.SetPosition(XMFLOAT3(0.0f, -3.0f, 0.0f));
	bird_stand.SetRotation(XMFLOAT3(0.0f, -1.0f, 0.0f));

	bird_body.SetData(dxutils.LoadModel("models/bird_main.obj"));
	bird_body.Create();

	light_source.Create();
	light_source.SetColour(XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f));
	light_source.SetPosition(DirectX::XMFLOAT3(5.0f, 0.0f, -4.1f));
}

/* Release the objects in the scene */
void TestScene::Release()
{
	main_cam.Release();
	bird_stand.Release();
	bird_body.Release();
	light_source.Release();
}

/* Update the objects in the scene */
bool TestScene::Update(double dt)
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

	bird_stand.Update(dt);
	bird_body.Update(dt);

	main_cam.Update(dt);

	ImGui::Begin("Test");
	ImGui::End();

	light_source.Update(dt);

	return true;
}

/* Render the objects in the scene */
void TestScene::Render(double dt)
{
	bird_stand.Render(dt);
	bird_body.Render(dt);
	light_source.Render(dt);
}
