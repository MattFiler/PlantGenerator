#include "PlantGeneration.h"
#include "GameObjectManager.h"

/* Initialise the plant generation (load OBJs) */
void PlantGeneration::Init()
{
	stem.SetData(dxutils.LoadModel("models/plant_parts/stem.obj"));
	petal.SetData(dxutils.LoadModel("models/plant_parts/petal_low.obj"));
	flower.SetData(dxutils.LoadModel("models/plant_parts/flower_middle_low.obj"));
	leaf.SetData(dxutils.LoadModel("models/plant_parts/leaf_low.obj"));

	flower.SetRotation(DirectX::XMFLOAT3(0.0f, 0.0f, XM_PI));
	flower.SetPosition(DirectX::XMFLOAT3(0.0f, 0.5f, 0.0f));

	//stem.SetInvisible(true);
	petal.SetInvisible(true);
	//flower.SetInvisible(true);
	leaf.SetInvisible(true);

	GameObjectManager::AddObject(&stem);
	GameObjectManager::AddObject(&petal);
	GameObjectManager::AddObject(&flower);
	GameObjectManager::AddObject(&leaf);
}

/* Render the generated plant */
void PlantGeneration::Render(float dt)
{
	petal.SetInvisible(false);
	for (int i = 0; i < petalRotations.size(); i++) {
		petal.SetRotation(petalRotations[i]);
		petal.Update(dt);
		petal.Render(dt);
		Debug::Log("Rendering at " + std::to_string(petalRotations[i].y));
	}
	petal.SetInvisible(true);
}

/* Set the number of petals and calculate their rotations */
void PlantGeneration::SetPetalCount(int count)
{
	if (petalRotations.size() == count) return;
	petalRotations.clear();
	float yPos = 0;
	for (int i = 0; i < count; i++) {
		petalRotations.push_back(DirectX::XMFLOAT3(XM_PI/7, yPos, XM_PI));
		yPos += XM_2PI / count;
	}
}