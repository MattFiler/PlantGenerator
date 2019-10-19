#include "Model.h"

/* Create all model parts */
void Model::Create()
{
	for (int i = 0; i < allModels.size(); i++) {
		allModels[i].Create();
	}
}

/* Release all model parts */
void Model::Release()
{
	for (int i = 0; i < allModels.size(); i++) {
		allModels[i].Release();
	}
}

/* Update all model parts */
void Model::Update(float dt)
{
	for (int i = 0; i < allModels.size(); i++) {
		allModels[i].Update(dt);
	}
}

/* Render all model parts */
void Model::Render(float dt)
{
	for (int i = 0; i < allModels.size(); i++) {
		allModels[i].Render(dt);
	}
}

/* Create all model parts within the model */
void Model::SetData(LoadedModel _m)
{
	for (int i = 0; i < _m.modelParts.size(); i++) {
		ModelPart newModel = ModelPart();
		newModel.SetData(_m.modelParts[i]);
		allModels.push_back(newModel);
	}
}
