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
		flower.SetScale(XMFLOAT3(size, flower.GetScale().y, size));
	}
	float GetStemThickness() {
		return stem.GetScale().x;
	}

	void SetPetalCount(int count);
	int GetPetalCount() {
		return (int)petalRotations.size();
	}

	void SetPetalScale(float scale) {
		petal.SetScale(scale);
	}
	float GetPetalScale() {
		return petal.GetScale().x;
	}

	void Init();
	void Render(float dt);

private:
	Utilities dxutils = Utilities();

	Model stem;
	Model petal;
	Model flower;
	Model leaf;

	std::vector<DirectX::XMFLOAT3> leafPositions;
	std::vector<DirectX::XMFLOAT3> leafRotations;
	std::vector<DirectX::XMFLOAT3> petalPositions;
	std::vector<DirectX::XMFLOAT3> petalRotations;
};

