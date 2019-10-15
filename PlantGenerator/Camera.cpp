#include "Camera.h"
#include <fstream>
#include <vector>

/* Create basic resources */
void Camera::Create()
{
	GameObject::Create();
}

/* Release the Camera */
void Camera::Release()
{
	GameObject::Release();
}

/* Update the Camera */
void Camera::Update(float dt)
{
	GameObject::Update(dt);
	dxshared::mView = mWorld;

	if (InputHandler::KeyPressed(WindowsKey::W)) {
		GameObject::SetPosition(XMFLOAT3(GameObject::GetPosition().x, GameObject::GetPosition().y, GameObject::GetPosition().z - dt));
	}
	if (InputHandler::KeyPressed(WindowsKey::S)) {
		GameObject::SetPosition(XMFLOAT3(GameObject::GetPosition().x, GameObject::GetPosition().y, GameObject::GetPosition().z + dt));
	}
	if (InputHandler::KeyPressed(WindowsKey::A)) {
		GameObject::SetPosition(XMFLOAT3(GameObject::GetPosition().x + dt, GameObject::GetPosition().y, GameObject::GetPosition().z));
	}
	if (InputHandler::KeyPressed(WindowsKey::D)) {
		GameObject::SetPosition(XMFLOAT3(GameObject::GetPosition().x - dt, GameObject::GetPosition().y, GameObject::GetPosition().z));
	}
	if (InputHandler::KeyPressed(WindowsKey::E)) {
		GameObject::SetRotation(XMFLOAT3(GameObject::GetRotation().x, GameObject::GetRotation().y - dt, GameObject::GetRotation().z));
	}
	if (InputHandler::KeyPressed(WindowsKey::Q)) {
		GameObject::SetRotation(XMFLOAT3(GameObject::GetRotation().x, GameObject::GetRotation().y + dt, GameObject::GetRotation().z));
	}
}
