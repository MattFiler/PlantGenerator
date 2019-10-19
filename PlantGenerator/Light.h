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
		LightManager::AddLight(this);
		LightManager::AddLight(this);
		LightManager::AddLight(this);
		LightManager::AddLight(this);
		LightManager::AddLight(this);
		LightManager::AddLight(this);
		LightManager::AddLight(this);
		LightManager::AddLight(this);
		LightManager::AddLight(this);
		LightManager::AddLight(this);
	}
	void Release() override {
		GameObject::Release();
	}
	void Update(float dt) override {
		GameObject::Update(dt);

		Debug::Log("Actual light pos = X:" + std::to_string(GameObject::GetPosition().x) + ", Y:" + std::to_string(GameObject::GetPosition().y) + ", Z:" + std::to_string(GameObject::GetPosition().z));
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
	XMFLOAT4 lightColour = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
};