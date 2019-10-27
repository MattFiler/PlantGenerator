#pragma once

#include "Scene.h"
#include "FlowerGenerator.h"

class TestScene3 : public Scene
{
public:
	void Init() override;
	void Release() override;

	bool Update(double dt) override;
	void Render(double dt) override;

private:
	Camera main_cam;
	Light light_source;

	FlowerGenerator flower_generator;
};

