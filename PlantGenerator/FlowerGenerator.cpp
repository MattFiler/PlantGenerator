#include "FlowerGenerator.h"
#include "GameObjectManager.h"

/* Initialise the flower generation (load OBJs) */
void FlowerGenerator::Init()
{
	std::fstream i("flower_config.json");
	i >> model_config;

	SetPolyLevel(0);
}

/* Render the generated flower */
void FlowerGenerator::Render(float dt)
{
	petal.SetInvisible(false);
	for (int i = 0; i < petalRotations.size(); i++) {
		petal.SetRotation(petalRotations[i]);
		petal.Update(dt);
		petal.Render(dt);
	}
	petal.SetInvisible(true);

	leaf.SetInvisible(false);
	for (int i = 0; i < leafPositions.size(); i++) {
		leaf.SetPosition(leafPositions[i]);
		leaf.SetRotation(leafRotations[i]);
		leaf.Update(dt);
		leaf.Render(dt);
	}
	leaf.SetInvisible(true);
}

/* Set the number of petals and calculate their rotations */
void FlowerGenerator::SetPetalCount(int count)
{
	if (petalRotations.size() == count) return;
	petalRotations.clear();
	float yPos = 0;
	for (int i = 0; i < count; i++) {
		petalRotations.push_back(DirectX::XMFLOAT3(petalTilt, yPos, XM_PI));
		yPos += XM_2PI / count;
	}
}

/* Swap between high or low poly models */
void FlowerGenerator::SetPolyLevel(int level)
{
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

	stem_data = dxutils.LoadModel(model_config["stem"]["models"][polyLevel]);
	stem.SetData(stem_data);
	stem.SetRotation(DirectX::XMFLOAT3(model_config["stem"]["rotation"][0], model_config["stem"]["rotation"][1], model_config["stem"]["rotation"][2]));
	stem.SetPosition(DirectX::XMFLOAT3(model_config["stem"]["position"][0], model_config["stem"]["position"][1], model_config["stem"]["position"][2]));

	petal_data = dxutils.LoadModel(model_config["petal"]["models"][polyLevel]);
	petal.SetData(petal_data);
	petal.SetRotation(DirectX::XMFLOAT3(model_config["petal"]["rotation"][0], model_config["petal"]["rotation"][1], model_config["petal"]["rotation"][2]));
	petal.SetPosition(DirectX::XMFLOAT3(model_config["petal"]["position"][0], model_config["petal"]["position"][1], model_config["petal"]["position"][2]));

	core_data = dxutils.LoadModel(model_config["core"]["models"][polyLevel]);
	core.SetData(core_data);
	core.SetRotation(DirectX::XMFLOAT3(model_config["core"]["rotation"][0], model_config["core"]["rotation"][1], model_config["core"]["rotation"][2]));
	core.SetPosition(DirectX::XMFLOAT3(model_config["core"]["position"][0], model_config["core"]["position"][1], model_config["core"]["position"][2]));

	leaf_data = dxutils.LoadModel(model_config["leaf"]["models"][polyLevel]);
	leaf.SetData(leaf_data);
	leaf.SetRotation(DirectX::XMFLOAT3(model_config["leaf"]["rotation"][0], model_config["leaf"]["rotation"][1], model_config["leaf"]["rotation"][2]));
	leaf.SetPosition(DirectX::XMFLOAT3(model_config["leaf"]["position"][0], model_config["leaf"]["position"][1], model_config["leaf"]["position"][2]));

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
}

/* Set the number of leaves */
void FlowerGenerator::SetLeafCount(int count, bool force)
{
	if (leafPositions.size() == count && !force) return;
	leafPositions.clear();
	float yPos = -2.0f;
	for (int i = 0; i < count; i++) {
		leafPositions.push_back(DirectX::XMFLOAT3(0.0f, yPos, 0.0f));
		yPos -= (stem.GetScale().y * stemLength) / count;
	}
	if (leafPositions.size() != leafRotations.size() || !force) RandomiseLeafRotations();
}

/* Randomise the rotation of all active leaves */
void FlowerGenerator::RandomiseLeafRotations()
{
	leafRotations.clear();
	for (int i = 0; i < leafPositions.size(); i++) {
		leafRotations.push_back(DirectX::XMFLOAT3(0.0f, static_cast<float>(rand())/(static_cast<float>(RAND_MAX / XM_2PI)), 0.0f));
	}
}

/* Get the polycount of the flower */
int FlowerGenerator::GetPolyCount()
{
	return core.GetVertCount() + stem.GetVertCount() + (leaf.GetVertCount() * GetLeafCount()) + (petal.GetVertCount() * GetPetalCount());
}

/* Save the generated flower as OBJ/MTL */
bool FlowerGenerator::Save(std::string path)
{
	LoadedModel finalOutput = LoadedModel();

	//Stem
	XMMATRIX stemWorld = XMMatrixScaling(stem.GetScale().x, stem.GetScale().y, stem.GetScale().z) *
						 XMMatrixRotationRollPitchYaw(stem.GetRotation().x, stem.GetRotation().y, stem.GetRotation().z) *
						 XMMatrixTranslation(stem.GetPosition().x, stem.GetPosition().y, stem.GetPosition().z);
	dxutils.TransformAndPush(stemWorld, stem_data, finalOutput);

	//Leaves
	for (int i = 0; i < leafRotations.size(); i++) {
		XMMATRIX thisWorld = XMMatrixScaling(leaf.GetScale().x, leaf.GetScale().y, leaf.GetScale().z) *
							 XMMatrixRotationRollPitchYaw(leafRotations[i].x, leafRotations[i].y, leafRotations[i].z) *
							 XMMatrixTranslation(leafPositions[i].x, leafPositions[i].y, leafPositions[i].z);
		dxutils.TransformAndPush(thisWorld, leaf_data, finalOutput);
	}

	//Flower middle
	XMMATRIX middleWorld = XMMatrixScaling(core.GetScale().x, core.GetScale().y, core.GetScale().z) *
						   XMMatrixRotationRollPitchYaw(core.GetRotation().x, core.GetRotation().y, core.GetRotation().z) *
						   XMMatrixTranslation(core.GetPosition().x, core.GetPosition().y, core.GetPosition().z);
	dxutils.TransformAndPush(middleWorld, core_data, finalOutput);

	//Petals
	for (int i = 0; i < petalRotations.size(); i++) {
		XMMATRIX thisWorld = XMMatrixScaling(petal.GetScale().x, petal.GetScale().y, petal.GetScale().z) *
							 XMMatrixRotationRollPitchYaw(petalRotations[i].x, petalRotations[i].y, petalRotations[i].z) *
							 XMMatrixTranslation(petal.GetPosition().x, petal.GetPosition().y, petal.GetPosition().z);
		dxutils.TransformAndPush(thisWorld, petal_data, finalOutput);
	}

	return dxutils.SaveModel(finalOutput, path);
}