#pragma once

#include "Scene.h"

class TestScene : public Scene
{
public:
	void Init() override;
	void Release() override;

	bool Update(double dt) override;
	void Render(double dt) override;

private:
	Camera main_cam = Camera();

	Model bird_stand = Model();
	Model bird_body = Model();
	bool goingForward = false;

	Light light_source = Light();
};

