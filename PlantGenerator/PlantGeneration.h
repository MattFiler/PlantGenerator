#pragma once

#include "dxutils.h"
#include "Model.h"

class PlantGeneration
{
public:
	PlantGeneration() = default;
	~PlantGeneration() = default;

	void SetStemLength(float len) {
		stem.SetScale(XMFLOAT3(stem.GetScale().x, len, stem.GetScale().z));
	}
	float GetStemLength() {
		return stem.GetScale().y;
	}

	void SetStemThickness(float size) {
		stem.SetScale(XMFLOAT3(size, stem.GetScale().y, size));
	}
	float GetStemThickness() {
		return stem.GetScale().x;
	}

	void Init();
	void Render(float dt);

private:
	Utilities dxutils = Utilities();

	Model stem;
	Model petal;
	Model leaf;
};

