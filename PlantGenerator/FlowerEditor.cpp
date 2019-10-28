#include "FlowerEditor.h"

/* Init the objects in the scene */
void FlowerEditor::Init()
{
	flower_generator = FlowerGenerator();
	flower_generator.Init();

	main_cam = Camera();
	light_source = Light();

	GameObjectManager::AddObject(&light_source);
	GameObjectManager::AddObject(&main_cam);
	GameObjectManager::Create();

	main_cam.SetPosition(DirectX::XMFLOAT3(-3.99f, 2.23f, 10.52f));
	main_cam.SetRotation(DirectX::XMFLOAT3(-0.93f, 0.0f, 0.0f));
	main_cam.SetLocked(true);
	light_source.SetIntensity(0.0f);
}

/* Release the objects in the scene */
void FlowerEditor::Release()
{
	GameObjectManager::Release();
}

/* Update the objects in the scene */
bool FlowerEditor::Update(double dt)
{
	int polyLevel = flower_generator.GetPolyLevel();
	int petalCount = flower_generator.GetPetalCount();
	float petalSize = flower_generator.GetPetalScale();
	float petalOffset = flower_generator.GetPetalOffset();
	float petalTilt = flower_generator.GetPetalTilt();
	int leafCount = flower_generator.GetLeafCount();
	float leafSize = flower_generator.GetLeafScale();
	float stemLen = flower_generator.GetStemLength();
	float stemThicc = flower_generator.GetStemThickness();
	bool camLock = main_cam.GetLocked();
	XMFLOAT3 lightPos = light_source.GetPosition();
	XMFLOAT4 lightCol = light_source.GetColour();
	float lightIntensity = light_source.GetIntensity();
	bool open = true;

	ImGui::SetNextWindowPos(ImVec2(950, 0));
	ImGui::SetNextWindowSize(ImVec2(330, 720));
	ImGui::Begin("Controls", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::Text("Flower Editor Controls");
	ImGui::Separator();
	ImGui::RadioButton("High Poly", &polyLevel, 0); ImGui::SameLine();
	ImGui::RadioButton("Medium Poly", &polyLevel, 1); ImGui::SameLine();
	ImGui::RadioButton("Low Poly", &polyLevel, 2);
	ImGui::Separator();
	ImGui::SliderInt("Petal Count", &petalCount, 0, 20);
	ImGui::SliderFloat("Petal Size", &petalSize, 0.0f, 20.0f);
	ImGui::SliderFloat("Petal Offset", &petalOffset, -20.0f, 20.0f);
	ImGui::SliderFloat("Petal Tilt", &petalTilt, -XM_2PI, XM_2PI);
	ImGui::Separator();
	ImGui::SliderInt("Leaf Count", &leafCount, 0, 20);
	if (ImGui::Button("Randomise Leaf Rotations"))
	{
		flower_generator.RandomiseLeafRotations();
	}
	ImGui::SliderFloat("Leaf Size", &leafSize, 0.0f, 20.0f);
	ImGui::Separator();
	ImGui::SliderFloat("Stem Length", &stemLen, 0.0f, 20.0f);
	ImGui::SliderFloat("Stem Width", &stemThicc, 0.0f, 20.0f);
	ImGui::Separator();
	ImGui::Dummy(ImVec2(0.0f, 40.0f));

	ImGui::Text("Scene Controls");
	ImGui::Separator();
	ImGui::Checkbox("Lock Camera", &camLock);
#ifdef _DEBUG
	ImGui::SameLine();
	ImGui::Checkbox("Enable Debugging", &dxshared::enableDebug);
#endif
	ImGui::Separator();
	ImGui::SliderFloat("Light X", &lightPos.x, -20.0f, 20.0f);
	ImGui::SliderFloat("Light Y", &lightPos.y, -20.0f, 20.0f);
	ImGui::SliderFloat("Light Z", &lightPos.z, -20.0f, 20.0f);
	ImGui::SliderFloat("Light Intensity", &lightIntensity, 0.0f, 20.0f);
	ImGui::SliderFloat("Light R", &lightCol.x, 0.0f, 1.0f);
	ImGui::SliderFloat("Light G", &lightCol.y, 0.0f, 1.0f);
	ImGui::SliderFloat("Light B", &lightCol.z, 0.0f, 1.0f);
	ImGui::Separator();
	ImGui::SliderFloat("Ambient R", &dxshared::ambientLightColour.x, 0.0f, 1.0f);
	ImGui::SliderFloat("Ambient G", &dxshared::ambientLightColour.y, 0.0f, 1.0f);
	ImGui::SliderFloat("Ambient B", &dxshared::ambientLightColour.z, 0.0f, 1.0f);
	ImGui::Separator();

	ImGui::Dummy(ImVec2(0.0f, 40.0f));
	ImGui::Text("Export Flower");
	ImGui::Separator();
	char filePath[128] = "";
	ImGui::Text("Output Filename");
	ImGui::SameLine();
	if (ImGui::InputText("", filePath, IM_ARRAYSIZE(filePath), ImGuiInputTextFlags_EnterReturnsTrue))
	{
		std::string filePathString(filePath);
		if (!flower_generator.Save(filePathString)) Debug::Log("Failed to save!!");
	}
	std::string vertCount = "Vertex Count = " + std::to_string(flower_generator.GetPolyCount());
	ImGui::Text(vertCount.c_str());
	ImGui::Separator();
	ImGui::End();

	flower_generator.SetPolyLevel(polyLevel);
	flower_generator.SetPetalCount(petalCount);
	flower_generator.SetPetalScale(petalSize);
	flower_generator.SetPetalOffset(petalOffset);
	flower_generator.SetPetalTilt(petalTilt);
	flower_generator.SetLeafCount(leafCount);
	flower_generator.SetLeafScale(leafSize);
	flower_generator.SetStemLength(stemLen);
	flower_generator.SetStemThickness(stemThicc);
	main_cam.SetLocked(camLock);
	light_source.SetPosition(lightPos);
	light_source.SetColour(lightCol);
	light_source.SetIntensity(lightIntensity);

	GameObjectManager::Update(dt);

	return true;
}

/* Render the objects in the scene */
void FlowerEditor::Render(double dt)
{
	GameObjectManager::Render(dt);
	flower_generator.Render(dt);
}
