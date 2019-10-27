#include "FlowerGenerator.h"
#include "GameObjectManager.h"

/* Initialise the flower generation (load OBJs) */
void FlowerGenerator::Init()
{
	stem.SetData(dxutils.LoadModel("models/plant_parts/stem.obj"));
	petal.SetData(dxutils.LoadModel("models/plant_parts/petal_low.obj"));
	core.SetData(dxutils.LoadModel("models/plant_parts/flower_middle_low.obj"));
	leaf.SetData(dxutils.LoadModel("models/plant_parts/leaf_low.obj"));

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
		petal.SetData(dxutils.LoadModel("models/plant_parts/petal.obj"));
		core.SetData(dxutils.LoadModel("models/plant_parts/flower_middle.obj"));
		leaf.SetData(dxutils.LoadModel("models/plant_parts/leaf.obj"));
	}
	else
	{
		petal.SetData(dxutils.LoadModel("models/plant_parts/petal_low.obj"));
		core.SetData(dxutils.LoadModel("models/plant_parts/flower_middle_low.obj"));
		leaf.SetData(dxutils.LoadModel("models/plant_parts/leaf_low.obj"));
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