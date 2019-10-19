#pragma once

#include "ModelPart.h"

class Model : public GameObject {
public:
	~Model() {
		Release();
	}

	void Create() override;
	void Release() override;
	void Update(float dt) override;
	void Render(float dt) override;

	void SetData(LoadedModel _m);

private:
	std::vector<ModelPart> allModels = std::vector<ModelPart>();
};