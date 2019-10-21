#pragma once

#include "GameObject.h"

class Light : public GameObject
{
public:
	~Light() {
		Release();
	}

	void Create() override {
		GameObject::Create();
	}
	void Release() override {
		GameObject::Release();
	}
	void Update(float dt) override {
		GameObject::Update(dt);
	}
	void Render(float dt) override {
		GameObject::Render(dt);
	}

	void SetColour(XMFLOAT4 _colour) {
		lightColour = _colour;
	}
	XMFLOAT4 GetColour() {
		return lightColour;
	}

private:
	XMFLOAT4 lightColour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
};