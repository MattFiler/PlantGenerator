#pragma once

#include <vector>

class Light;

class LightManager
{
public:
	LightManager() = default;
	~LightManager() {
		allLights.clear();
	}

	static void AddLight(Light* _aLight) {
		allLights.push_back(_aLight);
	}
	static std::vector<Light*> GetLights() {
		return allLights;
	}
	static int GetLightCount() {
		return allLights.size();
	}

private:
	static std::vector<Light*> allLights;
};

