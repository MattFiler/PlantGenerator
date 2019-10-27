#include "TestScene3.h"

/* Init the objects in the scene */
void TestScene3::Init()
{
	flower_generator.Init();

	main_cam = Camera();
	light_source = Light();

	GameObjectManager::AddObject(&light_source);
	GameObjectManager::AddObject(&main_cam);
	GameObjectManager::Create();

	main_cam.SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, 4.1f));

	light_source.SetColour(XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f));
	light_source.SetPosition(DirectX::XMFLOAT3(5.0f, 0.0f, -4.1f));

	flower_generator.SetStemLength(5.0f);
}

/* Release the objects in the scene */
void TestScene3::Release()
{
	GameObjectManager::Release();
}

/* Update the objects in the scene */
bool TestScene3::Update(double dt)
{
	bool highPoly = flower_generator.GetUseHighPoly();
	int petalCount = flower_generator.GetPetalCount();
	float petalSize = flower_generator.GetPetalScale();
	float petalOffset = flower_generator.GetPetalOffset();
	float petalTilt = flower_generator.GetPetalTilt();
	float stemLen = flower_generator.GetStemLength();
	float stemThicc = flower_generator.GetStemThickness();
	XMFLOAT3 lightPos = light_source.GetPosition();
	XMFLOAT4 lightCol = light_source.GetColour();
	float lightIntensity = light_source.GetIntensity();
	ImGui::Begin("TestScene3 Control");
	ImGui::Checkbox("High Poly", &highPoly);
	ImGui::Separator();
	ImGui::SliderInt("Petal Count", &petalCount, 0, 20);
	ImGui::SliderFloat("Petal Size", &petalSize, 0.0f, 20.0f);
	ImGui::SliderFloat("Petal Offset", &petalOffset, -20.0f, 20.0f);
	ImGui::SliderFloat("Petal Tilt", &petalTilt, -XM_2PI, XM_2PI);
	ImGui::Separator();
	ImGui::SliderFloat("Stem Length", &stemLen, 0.0f, 20.0f);
	ImGui::SliderFloat("Stem Width", &stemThicc, 0.0f, 20.0f);
	ImGui::Separator();
	ImGui::SliderFloat("Light X", &lightPos.x, -20.0f, 20.0f);
	ImGui::SliderFloat("Light Y", &lightPos.y, -20.0f, 20.0f);
	ImGui::SliderFloat("Light Z", &lightPos.z, -20.0f, 20.0f);
	ImGui::SliderFloat("Light Intensity", &lightIntensity, 0.0f, 20.0f);
	ImGui::SliderFloat("Light R", &lightCol.x, -1.0f, 1.0f);
	ImGui::SliderFloat("Light G", &lightCol.y, -1.0f, 1.0f);
	ImGui::SliderFloat("Light B", &lightCol.z, -1.0f, 1.0f);
	ImGui::Separator();
	ImGui::SliderFloat("Ambient R", &dxshared::ambientLightColour.x, -1.0f, 1.0f);
	ImGui::SliderFloat("Ambient G", &dxshared::ambientLightColour.y, -1.0f, 1.0f);
	ImGui::SliderFloat("Ambient B", &dxshared::ambientLightColour.z, -1.0f, 1.0f);
	ImGui::End();
	flower_generator.SetUseHighPoly(highPoly);
	flower_generator.SetPetalCount(petalCount);
	flower_generator.SetPetalScale(petalSize);
	flower_generator.SetPetalOffset(petalOffset);
	flower_generator.SetPetalTilt(petalTilt);
	flower_generator.SetStemLength(stemLen);
	flower_generator.SetStemThickness(stemThicc);
	light_source.SetPosition(lightPos);
	light_source.SetColour(lightCol);
	light_source.SetIntensity(lightIntensity);

	GameObjectManager::Update(dt);

	return true;
}

/* Render the objects in the scene */
void TestScene3::Render(double dt)
{
	GameObjectManager::Render(dt);
	flower_generator.Render(dt);
}
