#pragma once

#include "dxutils.h"
#include "Model.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

enum GrassSize {
	SMALL, MEDIUM, LARGE
};
class GrassBlade {
public:
	DirectX::XMFLOAT3 position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	GrassSize type = GrassSize::SMALL;
	int variant = 0;
};

class GrassGenerator
{
public:
	GrassGenerator() = default;
	~GrassGenerator() = default;

	void SetNumOfSmall(int count);
	int GetNumOfSmall() {
		return smallCount;
	}

	void SetSizeOfSmall(float size) {
		for (int i = 0; i < smallBlades.size(); i++) {
			smallBlades[i]->SetScale(size);
		}
	}
	float GetSizeOfSmall() {
		if (smallBlades.size() != 0)
			return smallBlades[0]->GetScale().x;
		else
			return 0.0f;
	}

	void SetDisplacementOfSmall(float dist);
	float GetDisplacementOfSmall() {
		return smallDispl;
	}

	void SetNumOfMedium(int count);
	int GetNumOfMedium() {
		return mediumCount;
	}

	void SetSizeOfMedium(float size) {
		for (int i = 0; i < mediumBlades.size(); i++) {
			mediumBlades[i]->SetScale(size);
		}
	}
	float GetSizeOfMedium() {
		if (mediumBlades.size() != 0)
			return mediumBlades[0]->GetScale().x;
		else
			return 0.0f;
	}

	void SetDisplacementOfMedium(float dist);
	float GetDisplacementOfMedium() {
		return mediumDispl;
	}

	void SetNumOfLarge(int count);
	int GetNumOfLarge() {
		return largeCount;
	}

	void SetSizeOfLarge(float size) {
		for (int i = 0; i < largeBlades.size(); i++) {
			largeBlades[i]->SetScale(size);
		}
	}
	float GetSizeOfLarge() {
		if (largeBlades.size() != 0)
			return largeBlades[0]->GetScale().x;
		else
			return 0.0f;
	}

	void SetDisplacementOfLarge(float dist);
	float GetDisplacementOfLarge() {
		return largeDispl;
	}

	void RandomisePositions(GrassSize type);
	void RandomiseRotations(GrassSize type);

	void SetPolyLevel(int level);
	int GetPolyLevel() {
		return polyLevel;
	}

	int GetPolyCount();

	bool Save(std::string path);

	void Init();
	void Render(float dt);

private:
	void RenderThisBlade(Model* blade, int setting_index, float dt);
	void SpawnNewBlade(int max_size, int diff, GrassSize type);
	float GetDisplacementOfType(GrassSize type) {
		if (type == GrassSize::SMALL) return GetDisplacementOfSmall();
		if (type == GrassSize::MEDIUM) return GetDisplacementOfMedium();
		if (type == GrassSize::LARGE) return GetDisplacementOfLarge();
		return 0.0f;
	}

	Utilities dxutils = Utilities();

	std::vector<Model*> smallBlades;
	std::vector<Model*> mediumBlades;
	std::vector<Model*> largeBlades;

	std::vector<LoadedModel> smallBlades_data;
	std::vector<LoadedModel> mediumBlades_data;
	std::vector<LoadedModel> largeBlades_data;

	json model_config;

	int polyLevel = -1;

	int smallCount = 0;
	int mediumCount = 0;
	int largeCount = 0;

	float smallDispl = 5.0f;
	float mediumDispl = 5.0f;
	float largeDispl = 5.0f;

	std::vector<GrassBlade> spawnedGrass;
};

