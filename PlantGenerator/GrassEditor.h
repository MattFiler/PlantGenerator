#pragma once

#include "Scene.h"
#include "GrassGenerator.h"

class GrassEditor : public Scene
{
public:
	void Init() override;
	void Release() override;

	bool Update(double dt) override;
	void Render(double dt) override;

private:
	Camera main_cam;
	Light light_source;

	GrassGenerator grass_generator;
};

