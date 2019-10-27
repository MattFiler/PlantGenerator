#pragma once

#include "Scene.h"

class BushEditor : public Scene
{
public:
	void Init() override;
	void Release() override;

	bool Update(double dt) override;
	void Render(double dt) override;

private:
	Camera main_cam;
	Model cube_model;
	Light light_source;
};

