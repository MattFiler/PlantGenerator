#pragma once

#include "GameObject.h"

class ModelPart : public GameObject
{
public:
	~ModelPart() {
		Release();
	}

	void Create() override;
	void Release() override;
	void Update(float dt) override;
	void Render(float dt) override;

	void SetData(LoadedModelPart _m) {
		modelMetaData = _m;
	}

protected:
	ID3D11Buffer* g_pConstantBuffer = nullptr;
	ID3D11Buffer* g_pIndexBuffer = nullptr;

	LoadedMaterial loadedMaterial = LoadedMaterial();
	LoadedModelPart modelMetaData = LoadedModelPart();

	int indexCount = 0;
};