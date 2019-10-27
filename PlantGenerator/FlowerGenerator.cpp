#include "FlowerGenerator.h"
#include "GameObjectManager.h"

/* Initialise the flower generation (load OBJs) */
void FlowerGenerator::Init()
{
	stem_data = dxutils.LoadModel("models/plant_parts/stem.obj");
	stem.SetData(stem_data);
	petal_data = dxutils.LoadModel("models/plant_parts/petal_low.obj");
	petal.SetData(petal_data);
	core_data = dxutils.LoadModel("models/plant_parts/flower_middle_low.obj");
	core.SetData(core_data);
	leaf_data = dxutils.LoadModel("models/plant_parts/leaf_low.obj");
	leaf.SetData(leaf_data);

	core.SetRotation(DirectX::XMFLOAT3(0.0f, 0.0f, XM_PI));
	core.SetPosition(DirectX::XMFLOAT3(0.0f, 0.5f, 0.0f));

	petal.SetInvisible(true);
	leaf.SetInvisible(true);

	GameObjectManager::AddObject(&stem);
	GameObjectManager::AddObject(&petal);
	GameObjectManager::AddObject(&core);
	GameObjectManager::AddObject(&leaf);
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
void FlowerGenerator::SetUseHighPoly(bool high)
{
	if (highPoly == high) return;
	highPoly = high;

	GameObjectManager::RemoveObject(&petal);
	GameObjectManager::RemoveObject(&core);
	GameObjectManager::RemoveObject(&leaf);

	petal = Model();
	core = Model();
	leaf = Model();

	if (highPoly) 
	{
		petal_data = dxutils.LoadModel("models/plant_parts/petal.obj");
		petal.SetData(petal_data);
		core_data = dxutils.LoadModel("models/plant_parts/flower_middle.obj");
		core.SetData(core_data);
		leaf_data = dxutils.LoadModel("models/plant_parts/leaf.obj");
		leaf.SetData(leaf_data);
	}
	else
	{
		petal_data = dxutils.LoadModel("models/plant_parts/petal_low.obj");
		petal.SetData(petal_data);
		core_data = dxutils.LoadModel("models/plant_parts/flower_middle_low.obj");
		core.SetData(core_data);
		leaf_data = dxutils.LoadModel("models/plant_parts/leaf_low.obj");
		leaf.SetData(leaf_data);
	}

	core.SetRotation(DirectX::XMFLOAT3(0.0f, 0.0f, XM_PI));
	core.SetPosition(DirectX::XMFLOAT3(0.0f, 0.5f, 0.0f));

	petal.SetInvisible(true);
	leaf.SetInvisible(true);

	petal.Create();
	core.Create();
	leaf.Create();

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
