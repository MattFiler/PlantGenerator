#include "GrassGenerator.h"
#include "GameObjectManager.h"

/* Initialise the grass generation (load OBJs) */
void GrassGenerator::Init()
{
	//Small grass blades
	for (int i = 0; i < 1; i++) {
		LoadedModel thisData = dxutils.LoadModel("models/grass_parts/small_" + std::to_string(i) + ".obj");
		smallBlades_data.push_back(&thisData);

		Model* thisModel = new Model();
		thisModel->SetData(thisData);
		thisModel->SetInvisible(true);
		smallBlades.push_back(thisModel);
		GameObjectManager::AddObject(thisModel);
	}

	//Medium grass blades
	for (int i = 0; i < 6; i++) {
		LoadedModel thisData = dxutils.LoadModel("models/grass_parts/medium_" + std::to_string(i) + ".obj");
		mediumBlades_data.push_back(&thisData);

		Model* thisModel = new Model();
		thisModel->SetData(thisData);
		thisModel->SetInvisible(true);
		mediumBlades.push_back(thisModel);
		GameObjectManager::AddObject(thisModel);
	}

	//Large grass blades
	for (int i = 0; i < 13; i++) {
		LoadedModel thisData = dxutils.LoadModel("models/grass_parts/large_" + std::to_string(i) + ".obj");
		largeBlades_data.push_back(&thisData);

		Model* thisModel = new Model();
		thisModel->SetData(thisData);
		thisModel->SetInvisible(true);
		largeBlades.push_back(thisModel);
		GameObjectManager::AddObject(thisModel);
	}
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
			spawnedGrass[i].position = XMFLOAT3(0.0f, static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / GetDisplacementOfType(type))), static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / GetDisplacementOfType(type))));
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
			newBlade.position = XMFLOAT3(0.0f, 0.0f, static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / GetDisplacementOfType(type))));
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
	/*
	if (polyLevel == level) return;
	polyLevel = level;

	GameObjectManager::RemoveObject(&stem);
	GameObjectManager::RemoveObject(&petal);
	GameObjectManager::RemoveObject(&core);
	GameObjectManager::RemoveObject(&leaf);

	stem.Release();
	petal.Release();
	core.Release();
	leaf.Release();

	stem = Model();
	petal = Model();
	core = Model();
	leaf = Model();

	switch (polyLevel)
	{
	case 0:
		stem_data = dxutils.LoadModel("models/plant_parts/stem.obj");
		stem.SetData(stem_data);
		petal_data = dxutils.LoadModel("models/plant_parts/petal.obj");
		petal.SetData(petal_data);
		core_data = dxutils.LoadModel("models/plant_parts/flower_middle.obj");
		core.SetData(core_data);
		leaf_data = dxutils.LoadModel("models/plant_parts/leaf.obj");
		leaf.SetData(leaf_data);
		break;
	case 1:
		stem_data = dxutils.LoadModel("models/plant_parts/stem_low.obj");
		stem.SetData(stem_data);
		petal_data = dxutils.LoadModel("models/plant_parts/petal_low.obj");
		petal.SetData(petal_data);
		core_data = dxutils.LoadModel("models/plant_parts/flower_middle_low.obj");
		core.SetData(core_data);
		leaf_data = dxutils.LoadModel("models/plant_parts/leaf_low.obj");
		leaf.SetData(leaf_data);
		break;
	case 2:
		stem_data = dxutils.LoadModel("models/plant_parts/stem_lower.obj");
		stem.SetData(stem_data);
		petal_data = dxutils.LoadModel("models/plant_parts/petal_lower.obj");
		petal.SetData(petal_data);
		core_data = dxutils.LoadModel("models/plant_parts/flower_middle_lower.obj");
		core.SetData(core_data);
		leaf_data = dxutils.LoadModel("models/plant_parts/leaf_lower.obj");
		leaf.SetData(leaf_data);
		break;
	}

	core.SetRotation(DirectX::XMFLOAT3(0.0f, 0.0f, XM_PI));
	core.SetPosition(DirectX::XMFLOAT3(0.0f, 0.5f, 0.0f));

	petal.SetInvisible(true);
	leaf.SetInvisible(true);

	stem.Create();
	petal.Create();
	core.Create();
	leaf.Create();

	GameObjectManager::AddObject(&stem);
	GameObjectManager::AddObject(&petal);
	GameObjectManager::AddObject(&core);
	GameObjectManager::AddObject(&leaf);
	*/
}

/* Save the generated flower as OBJ/MTL */
bool GrassGenerator::Save(std::string path)
{
	/*
	LoadedModel finalOutput = LoadedModel();

	//Stem
	XMMATRIX stemWorld = XMMatrixScaling(stem.GetScale().x, stem.GetScale().y, stem.GetScale().z) *
		XMMatrixTranslation(stem.GetPosition().x, stem.GetPosition().y, stem.GetPosition().z) *
		XMMatrixRotationRollPitchYaw(stem.GetRotation().x, stem.GetRotation().y, stem.GetRotation().z);
	dxutils.TransformAndPush(stemWorld, stem_data, finalOutput);

	//Leaves
	for (int i = 0; i < leafRotations.size(); i++) {
		XMMATRIX thisWorld = XMMatrixScaling(leaf.GetScale().x, leaf.GetScale().y, leaf.GetScale().z) *
			XMMatrixTranslation(leafPositions[i].x, leafPositions[i].y, leafPositions[i].z) *
			XMMatrixRotationRollPitchYaw(leafRotations[i].x, leafRotations[i].y, leafRotations[i].z);
		dxutils.TransformAndPush(thisWorld, leaf_data, finalOutput);
	}

	//Flower middle
	XMMATRIX middleWorld = XMMatrixScaling(core.GetScale().x, core.GetScale().y, core.GetScale().z) *
		XMMatrixTranslation(core.GetPosition().x, core.GetPosition().y, core.GetPosition().z) *
		XMMatrixRotationRollPitchYaw(core.GetRotation().x, core.GetRotation().y, core.GetRotation().z);
	dxutils.TransformAndPush(middleWorld, core_data, finalOutput);

	//Petals
	for (int i = 0; i < petalRotations.size(); i++) {
		XMMATRIX thisWorld = XMMatrixScaling(petal.GetScale().x, petal.GetScale().y, petal.GetScale().z) *
			XMMatrixTranslation(petal.GetPosition().x, petal.GetPosition().y, petal.GetPosition().z) *
			XMMatrixRotationRollPitchYaw(petalRotations[i].x, petalRotations[i].y, petalRotations[i].z);
		dxutils.TransformAndPush(thisWorld, petal_data, finalOutput);
	}

	return dxutils.SaveModel(finalOutput, path);
	*/
	return false;
}