#include "BushEditor.h"

/* Init the objects in the scene */
void BushEditor::Init()
{
	Utilities dxutils = Utilities();

	main_cam = Camera();
	light_source = Light();

	GameObjectManager::AddObject(&light_source);
	GameObjectManager::AddObject(&main_cam);
	GameObjectManager::Create();

	main_cam.SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, 4.1f));

	light_source.SetColour(XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f));
	light_source.SetPosition(DirectX::XMFLOAT3(5.0f, 0.0f, -4.1f));
}

/* Release the objects in the scene */
void BushEditor::Release()
{
	GameObjectManager::Release();
}

/* Update the objects in the scene */
bool BushEditor::Update(double dt)
{
	XMFLOAT3 lightPos = light_source.GetPosition();
	XMFLOAT4 lightCol = light_source.GetColour();
	float lightIntensity = light_source.GetIntensity();
	bool camLock = main_cam.GetLocked();
	bool open = true;

	ImGui::SetNextWindowPos(ImVec2(950, 0));
	ImGui::SetNextWindowSize(ImVec2(330, 720));
	ImGui::Begin("Controls", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::Text("Bush Editor Controls");
	ImGui::Separator();
	ImGui::Dummy(ImVec2(0.0f, 45.0f));

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
	ImGui::End();

	light_source.SetPosition(lightPos);
	light_source.SetColour(lightCol);
	light_source.SetIntensity(lightIntensity);
	main_cam.SetLocked(camLock);

	GameObjectManager::Update(dt);

	return true;
}

/* Render the objects in the scene */
void BushEditor::Render(double dt)
{
	GameObjectManager::Render(dt);
}
