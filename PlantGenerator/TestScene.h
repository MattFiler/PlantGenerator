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
	Camera main_cam;

	Model bird_stand;
	Model bird_body;

	bool doAnimation = true;
	bool goingForward = false;

	Light light_source;
};

