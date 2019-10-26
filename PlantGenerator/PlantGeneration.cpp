#include "PlantGeneration.h"
#include "GameObjectManager.h"

/* Initialise the plant generation (load OBJs) */
void PlantGeneration::Init()
{
	stem.SetData(dxutils.LoadModel("models/plant_parts/stem.obj"));
	petal.SetData(dxutils.LoadModel("models/plant_parts/petal_low.obj"));
	leaf.SetData(dxutils.LoadModel("models/plant_parts/leaf_low.obj"));

	//stem.SetInvisible(true);
	petal.SetInvisible(true);
	leaf.SetInvisible(true);

	GameObjectManager::AddObject(&stem);
	GameObjectManager::AddObject(&petal);
	GameObjectManager::AddObject(&leaf);
}

/* Render the generated plant */
void PlantGeneration::Render(float dt)
{
	//note to self - this is how i'll render leaves and petals - use the one loaded object and just redraw in different positions
	//come up with a way to do this neatly and dynamically
	petal.SetInvisible(false);
	petal.SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	petal.Update(dt);
	petal.Render(dt);
	petal.SetPosition(XMFLOAT3(5.0f, 0.0f, 0.0f));
	petal.Update(dt);
	petal.Render(dt);
	petal.SetInvisible(true);
}
