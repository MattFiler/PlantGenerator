#include "GrassGenerator.h"
#include "GameObjectManager.h"

/* Initialise the grass generation (load OBJs) */
void GrassGenerator::Init()
{
	std::fstream i("grass_config.json");
	i >> model_config;

	SetPolyLevel(0);
}

/* Render the generated grass */
void GrassGenerator::Render(float dt)
{
	for (int i = 0; i < spawnedGrass.size(); i++) {
		switch (spawnedGrass[i].type) {
		case GrassSize::SMALL:
			RenderThisBlade(smallBlades[spawnedGrass[i].variant], i, dt);
			break;
		case GrassSize::MEDIUM:
			RenderThisBlade(mediumBlades[spawnedGrass[i].variant], i, dt);
			break;
		case GrassSize::LARGE:
			RenderThisBlade(largeBlades[spawnedGrass[i].variant], i, dt);
			break;
		}
	}
}
void GrassGenerator::RenderThisBlade(Model* blade, int setting_index, float dt)
{
	blade->SetInvisible(false);
	blade->SetRotation(spawnedGrass[setting_index].rotation);
	blade->SetPosition(spawnedGrass[setting_index].position);
	blade->Update(dt);
	blade->Render(dt);
	blade->SetInvisible(true);
}

/* Set the number of small blades */
void GrassGenerator::SetNumOfSmall(int count)
{
	if (smallCount == count) return;
	int diff = count - smallCount;
	smallCount = count;
	SpawnNewBlade(smallBlades.size(), diff, GrassSize::SMALL);
}

/* Set the displacement of small blades */
void GrassGenerator::SetDisplacementOfSmall(float dist)
{
	if (smallDispl == dist) return;
	smallDispl = dist;
	RandomisePositions(GrassSize::SMALL);
}

/* Set the number of medium blades */
void GrassGenerator::SetNumOfMedium(int count)
{
	if (mediumCount == count) return;
	int diff = count - mediumCount;
	mediumCount = count;
	SpawnNewBlade(mediumBlades.size(), diff, GrassSize::MEDIUM);
}

/* Set the displacement of medium blades */
void GrassGenerator::SetDisplacementOfMedium(float dist)
{
	if (mediumDispl == dist) return;
	mediumDispl = dist;
	RandomisePositions(GrassSize::MEDIUM);
}

/* Set the number of large blades */
void GrassGenerator::SetNumOfLarge(int count)
{
	if (largeCount == count) return;
	int diff = count - largeCount;
	largeCount = count;
	SpawnNewBlade(largeBlades.size(), diff, GrassSize::LARGE);
}

/* Set the displacement of large blades */
void GrassGenerator::SetDisplacementOfLarge(float dist)
{
	if (largeDispl == dist) return;
	largeDispl = dist;
	RandomisePositions(GrassSize::LARGE);
}

/* Randomise positions */
void GrassGenerator::RandomisePositions(GrassSize type)
{
	for (int i = 0; i < spawnedGrass.size(); i++) {
		if (spawnedGrass[i].type == type) {
			spawnedGrass[i].position = XMFLOAT3(static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / GetDisplacementOfType(type))), 0.0f, static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / GetDisplacementOfType(type))));
		}
	}
}

/* Randomise rotations */
void GrassGenerator::RandomiseRotations(GrassSize type)
{
	for (int i = 0; i < spawnedGrass.size(); i++) {
		if (spawnedGrass[i].type == type) {
			spawnedGrass[i].rotation = XMFLOAT3(0.0f, static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / XM_2PI)), 0.0f);
		}
	}
}

/* Spawn a blade */
void GrassGenerator::SpawnNewBlade(int max_size, int diff, GrassSize type)
{
	if (diff > 0) {
		for (int i = 0; i < diff; i++) {
			GrassBlade newBlade = GrassBlade();
			newBlade.type = type;
			newBlade.variant = rand() % max_size;
			newBlade.rotation = XMFLOAT3(0.0f, static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / XM_2PI)), 0.0f);
			newBlade.position = XMFLOAT3(static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / GetDisplacementOfType(type))), 0.0f, static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / GetDisplacementOfType(type))));
			spawnedGrass.push_back(newBlade);
		}
	}
	else {
		diff *= -1;
		for (int i = 0; i < diff; i++) {
			for (int x = spawnedGrass.size() - 1; x >= 0; x--) {
				if (spawnedGrass[x].type == type) {
					spawnedGrass.erase(spawnedGrass.begin() + x);
					break;
				}
			}
		}
	}
}

/* Swap between high or low poly models */
void GrassGenerator::SetPolyLevel(int level)
{
	if (polyLevel == level) return;
	polyLevel = level;
	
	//Unload all small/medium/large current LOD
	smallBlades_data.clear();
	for (int i = 0; i < smallBlades.size(); i++) {
		smallBlades[i]->Release();
		GameObjectManager::RemoveObject(smallBlades[i]);
	}
	smallBlades.clear();
	mediumBlades_data.clear();
	for (int i = 0; i < mediumBlades.size(); i++) {
		mediumBlades[i]->Release();
		GameObjectManager::RemoveObject(mediumBlades[i]);
	}
	mediumBlades.clear();
	largeBlades_data.clear();
	for (int i = 0; i < largeBlades.size(); i++) {
		largeBlades[i]->Release();
		GameObjectManager::RemoveObject(largeBlades[i]);
	}
	largeBlades.clear();
	
	std::string qualityType = "models_hq";
	if (level == 1) qualityType = "models_lq";

	//Small grass blades
	for (int i = 0; i < model_config["small"][qualityType].size(); i++) {
		smallBlades_data.push_back(dxutils.LoadModel(model_config["small"][qualityType][i]));

		Model* thisModel = new Model();
		thisModel->SetData(smallBlades_data[i]);
		thisModel->SetInvisible(true);
		thisModel->Create();
		smallBlades.push_back(thisModel);
		GameObjectManager::AddObject(thisModel);
	}

	//Medium grass blades
	for (int i = 0; i < model_config["medium"][qualityType].size(); i++) {
		mediumBlades_data.push_back(dxutils.LoadModel(model_config["medium"][qualityType][i]));

		Model* thisModel = new Model();
		thisModel->SetData(mediumBlades_data[i]);
		thisModel->SetInvisible(true);
		thisModel->Create();
		mediumBlades.push_back(thisModel);
		GameObjectManager::AddObject(thisModel);
	}

	//Large grass blades
	for (int i = 0; i < model_config["large"][qualityType].size(); i++) {
		largeBlades_data.push_back(dxutils.LoadModel(model_config["large"][qualityType][i]));

		Model* thisModel = new Model();
		thisModel->SetData(largeBlades_data[i]);
		thisModel->SetInvisible(true);
		thisModel->Create();
		largeBlades.push_back(thisModel);
		GameObjectManager::AddObject(thisModel);
	}
}

/* Get the polycount of the grass */
int GrassGenerator::GetPolyCount()
{
	int count = 0;
	for (int i = 0; i < spawnedGrass.size(); i++) {
		switch (spawnedGrass[i].type) {
		case GrassSize::SMALL:
			count += smallBlades[spawnedGrass[i].variant]->GetVertCount();
			break;
		case GrassSize::MEDIUM:
			count += mediumBlades[spawnedGrass[i].variant]->GetVertCount();
			break;
		case GrassSize::LARGE:
			count += largeBlades[spawnedGrass[i].variant]->GetVertCount();
			break;
		}
	}
	return count;
}

/* Save the generated flower as OBJ/MTL */
bool GrassGenerator::Save(std::string path)
{
	LoadedModel finalOutput = LoadedModel();

	for (int i = 0; i < spawnedGrass.size(); i++) {
		switch (spawnedGrass[i].type) {
		case GrassSize::SMALL:
			XMMATRIX thisWorld = XMMatrixScaling(smallBlades[spawnedGrass[i].variant]->GetScale().x, smallBlades[spawnedGrass[i].variant]->GetScale().y, smallBlades[spawnedGrass[i].variant]->GetScale().z) *
				XMMatrixRotationRollPitchYaw(spawnedGrass[i].rotation.x, spawnedGrass[i].rotation.y, spawnedGrass[i].rotation.z) *
				XMMatrixTranslation(spawnedGrass[i].position.x, spawnedGrass[i].position.y, spawnedGrass[i].position.z);
			dxutils.TransformAndPush(thisWorld, smallBlades_data[spawnedGrass[i].variant], finalOutput);
			break;
		case GrassSize::MEDIUM:
			XMMATRIX thisWorld2 = XMMatrixScaling(mediumBlades[spawnedGrass[i].variant]->GetScale().x, mediumBlades[spawnedGrass[i].variant]->GetScale().y, mediumBlades[spawnedGrass[i].variant]->GetScale().z) *
				XMMatrixRotationRollPitchYaw(spawnedGrass[i].rotation.x, spawnedGrass[i].rotation.y, spawnedGrass[i].rotation.z) *
				XMMatrixTranslation(spawnedGrass[i].position.x, spawnedGrass[i].position.y, spawnedGrass[i].position.z);
			dxutils.TransformAndPush(thisWorld2, mediumBlades_data[spawnedGrass[i].variant], finalOutput);
			break;
		case GrassSize::LARGE:
			XMMATRIX thisWorld3 = XMMatrixScaling(largeBlades[spawnedGrass[i].variant]->GetScale().x, largeBlades[spawnedGrass[i].variant]->GetScale().y, largeBlades[spawnedGrass[i].variant]->GetScale().z) *
				XMMatrixRotationRollPitchYaw(spawnedGrass[i].rotation.x, spawnedGrass[i].rotation.y, spawnedGrass[i].rotation.z) *
				XMMatrixTranslation(spawnedGrass[i].position.x, spawnedGrass[i].position.y, spawnedGrass[i].position.z);
			dxutils.TransformAndPush(thisWorld3, largeBlades_data[spawnedGrass[i].variant], finalOutput);
			break;
		}
	}

	return dxutils.SaveModel(finalOutput, path);
}