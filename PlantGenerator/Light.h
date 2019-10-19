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

		//A BODGE FOR NOW - SHOULD ONLY ADD THIS LIGHT ONCE, BUT HLSL IS SHIT AND WE NEED THE MAX FOR SOME FUCKING REASON
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

		double moveSpeed = dt;
		if (InputHandler::KeyPressed(WindowsKey::SHIFT)) {
			moveSpeed *= 4;
		}
		if (InputHandler::KeyPressed(WindowsKey::W)) {
			GameObject::SetPosition(XMFLOAT3(GameObject::GetPosition().x, GameObject::GetPosition().y, GameObject::GetPosition().z - moveSpeed));
		}
		if (InputHandler::KeyPressed(WindowsKey::S)) {
			GameObject::SetPosition(XMFLOAT3(GameObject::GetPosition().x, GameObject::GetPosition().y, GameObject::GetPosition().z + moveSpeed));
		}
		if (InputHandler::KeyPressed(WindowsKey::A)) {
			GameObject::SetPosition(XMFLOAT3(GameObject::GetPosition().x + moveSpeed, GameObject::GetPosition().y, GameObject::GetPosition().z));
		}
		if (InputHandler::KeyPressed(WindowsKey::D)) {
			GameObject::SetPosition(XMFLOAT3(GameObject::GetPosition().x - moveSpeed, GameObject::GetPosition().y, GameObject::GetPosition().z));
		}
		if (InputHandler::KeyPressed(WindowsKey::E)) {
			GameObject::SetRotation(XMFLOAT3(GameObject::GetRotation().x, GameObject::GetRotation().y - dt, GameObject::GetRotation().z));
		}
		if (InputHandler::KeyPressed(WindowsKey::Q)) {
			GameObject::SetRotation(XMFLOAT3(GameObject::GetRotation().x, GameObject::GetRotation().y + dt, GameObject::GetRotation().z));
		}
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