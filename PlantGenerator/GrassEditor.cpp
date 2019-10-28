#include "GrassEditor.h"

/* Init the objects in the scene */
void GrassEditor::Init()
{
	grass_generator = GrassGenerator();
	grass_generator.Init();

	main_cam = Camera();
	light_source = Light();

	GameObjectManager::AddObject(&light_source);
	GameObjectManager::AddObject(&main_cam);
	GameObjectManager::Create();

	main_cam.SetPosition(DirectX::XMFLOAT3(-0.82f, -2.34f, 2.9f));
	main_cam.SetRotation(DirectX::XMFLOAT3(-0.37f, -1.1f, 0.5f));
	main_cam.SetLocked(true);
	light_source.SetIntensity(0.0f);
}

/* Release the objects in the scene */
void GrassEditor::Release()
{
	GameObjectManager::Release();
}

/* Update the objects in the scene */
bool GrassEditor::Update(double dt)
{
	int polyLevel = grass_generator.GetPolyLevel();
	int smlCount = grass_generator.GetNumOfSmall();
	float smlSize = grass_generator.GetSizeOfSmall();
	float smlDist = grass_generator.GetDisplacementOfSmall();
	int medCount = grass_generator.GetNumOfMedium();
	float medSize = grass_generator.GetSizeOfMedium();
	float medDist = grass_generator.GetDisplacementOfMedium();
	int lrgCount = grass_generator.GetNumOfLarge();
	float lrgSize = grass_generator.GetSizeOfLarge();
	float lrgDist = grass_generator.GetDisplacementOfLarge();
	XMFLOAT3 lightPos = light_source.GetPosition();
	XMFLOAT4 lightCol = light_source.GetColour();
	float lightIntensity = light_source.GetIntensity();
	bool camLock = main_cam.GetLocked();
	bool open = true;

	ImGui::SetNextWindowPos(ImVec2(950, 0));
	ImGui::SetNextWindowSize(ImVec2(330, 720));
	ImGui::Begin("Controls", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::Text("Grass Editor Controls");
	ImGui::Separator();
	ImGui::RadioButton("High Poly", &polyLevel, 0); ImGui::SameLine();
	ImGui::RadioButton("Low Poly", &polyLevel, 1);
	ImGui::Separator();
	ImGui::SliderInt("Small Count", &smlCount, 0, 1000);
	ImGui::SliderFloat("Small Size", &smlSize, 0.0f, 20.0f);
	ImGui::SliderFloat("Small Area", &smlDist, 0.0f, 100.0f);
	if (ImGui::Button("Randomise S Positions"))
	{
		grass_generator.RandomisePositions(GrassSize::SMALL);
	}
	ImGui::SameLine();
	if (ImGui::Button("Randomise S Rotations"))
	{
		grass_generator.RandomiseRotations(GrassSize::SMALL);
	}
	ImGui::Separator();
	ImGui::SliderInt("Medium Count", &medCount, 0, 1000);
	ImGui::SliderFloat("Medium Size", &medSize, 0.0f, 20.0f);
	ImGui::SliderFloat("Medium Area", &medDist, 0.0f, 100.0f);
	if (ImGui::Button("Randomise M Positions"))
	{
		grass_generator.RandomisePositions(GrassSize::MEDIUM);
	}
	ImGui::SameLine();
	if (ImGui::Button("Randomise M Rotations"))
	{
		grass_generator.RandomiseRotations(GrassSize::MEDIUM);
	}
	ImGui::Separator();
	ImGui::SliderInt("Large Count", &lrgCount, 0, 1000);
	ImGui::SliderFloat("Large Size", &lrgSize, 0.0f, 20.0f);
	ImGui::SliderFloat("Large Area", &lrgDist, 0.0f, 100.0f);
	if (ImGui::Button("Randomise L Positions"))
	{
		grass_generator.RandomisePositions(GrassSize::LARGE);
	}
	ImGui::SameLine();
	if (ImGui::Button("Randomise L Rotations"))
	{
		grass_generator.RandomiseRotations(GrassSize::LARGE);
	}
	ImGui::Separator();
	ImGui::Dummy(ImVec2(0.0f, 3.0f));

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

	ImGui::Dummy(ImVec2(0.0f, 3.0f));
	ImGui::Text("Export Grass");
	ImGui::Separator();
	char filePath[128] = "";
	ImGui::Text("Output Filename");
	ImGui::SameLine();
	if (ImGui::InputText("", filePath, IM_ARRAYSIZE(filePath), ImGuiInputTextFlags_EnterReturnsTrue))
	{
		std::string filePathString(filePath);
		if (!grass_generator.Save(filePathString)) Debug::Log("Failed to save!!");
	}
	std::string vertCount = "Vertex Count = " + std::to_string(grass_generator.GetPolyCount());
	ImGui::Text(vertCount.c_str());
	ImGui::Separator();
	ImGui::End();

	grass_generator.SetPolyLevel(polyLevel);
	grass_generator.SetNumOfSmall(smlCount);
	grass_generator.SetSizeOfSmall(smlSize);
	grass_generator.SetDisplacementOfSmall(smlDist);
	grass_generator.SetNumOfMedium(medCount);
	grass_generator.SetSizeOfMedium(medSize);
	grass_generator.SetDisplacementOfMedium(medDist);
	grass_generator.SetNumOfLarge(lrgCount);
	grass_generator.SetSizeOfLarge(lrgSize);
	grass_generator.SetDisplacementOfLarge(lrgDist);
	light_source.SetPosition(lightPos);
	light_source.SetColour(lightCol);
	light_source.SetIntensity(lightIntensity);
	main_cam.SetLocked(camLock);

	GameObjectManager::Update(dt);

	return true;
}

/* Render the objects in the scene */
void GrassEditor::Render(double dt)
{
	GameObjectManager::Render(dt);
	grass_generator.Render(dt);
}
