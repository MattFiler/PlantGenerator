#pragma once

#include "dxutils.h"
#include "Model.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class FlowerGenerator
{
public:
	FlowerGenerator() = default;
	~FlowerGenerator() = default;

	void SetStemLength(float len) {
		stem.SetScale(XMFLOAT3(stem.GetScale().x, len, stem.GetScale().z));
		SetLeafCount(GetLeafCount(), true);
	}
	float GetStemLength() {
		return stem.GetScale().y;
	}

	void SetStemThickness(float size) {
		stem.SetScale(XMFLOAT3(size, stem.GetScale().y, size));
		core.SetScale(XMFLOAT3(size, core.GetScale().y, size));
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

	void SetPetalOffset(float offset) {
		petal.SetPosition(XMFLOAT3(0.0f, offset, 0.0f));
	}
	float GetPetalOffset() {
		return petal.GetPosition().y;
	}

	void SetPetalTilt(float tilt) {
		if (petalTilt == tilt) return;
		petalTilt = tilt;
		for (int i = 0; i < petalRotations.size(); i++) {
			petalRotations[i] = (XMFLOAT3(petalTilt, petalRotations[i].y, petalRotations[i].z));
		}
	}
	float GetPetalTilt() {
		return petalTilt;
	}

	void SetPolyLevel(int level);
	int GetPolyLevel() {
		return polyLevel;
	}

	void SetLeafCount(int count, bool force = false);
	int GetLeafCount() {
		return (int)leafPositions.size();
	}

	void RandomiseLeafRotations();

	void SetLeafScale(float scale) {
		leaf.SetScale(scale);
	}
	float GetLeafScale() {
		return leaf.GetScale().x;
	}

	int GetPolyCount();

	bool Save(std::string path);

	void Init();
	void Render(float dt);

private:
	Utilities dxutils = Utilities();

	Model stem;
	Model petal;
	Model core;
	Model leaf;

	LoadedModel stem_data;
	LoadedModel petal_data;
	LoadedModel core_data;
	LoadedModel leaf_data;

	json model_config;

	int polyLevel = -1;
	float petalTilt = XM_PI / 7;
	float stemLength = 14.0f;

	std::vector<DirectX::XMFLOAT3> leafPositions;
	std::vector<DirectX::XMFLOAT3> leafRotations;
	std::vector<DirectX::XMFLOAT3> petalRotations;
};

