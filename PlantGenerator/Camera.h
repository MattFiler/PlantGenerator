#pragma once

#include "GameObject.h"

class Camera : public GameObject
{
public:
	~Camera() {
		Release();
	}

	void Create() override;
	void Release() override;
	void Update(float dt) override;
	void Render(float dt) override {
		//GameObject::Render(dt);
	}
};