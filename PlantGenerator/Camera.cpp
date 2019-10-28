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

	if (!isActive) return;
	dxshared::mView = mWorld;
	//dxshared::mView = XMMatrixScaling(scale.x, scale.y, scale.z) * XMMatrixTranslation(position.x, position.y, position.z) * XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

	if (dxshared::enableDebug && InputHandler::KeyPressed(WindowsKey::O)) {
		Debug::Log("Camera position = X:" + std::to_string(GameObject::GetPosition().x) + ", Y:" + std::to_string(GameObject::GetPosition().y) + ", Z:" + std::to_string(GameObject::GetPosition().z));
		Debug::Log("Camera rotation = X:" + std::to_string(GameObject::GetRotation().x) + ", Y:" + std::to_string(GameObject::GetRotation().y) + ", Z:" + std::to_string(GameObject::GetRotation().z));
	}

	if (isLocked) return;
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
	if (InputHandler::KeyPressed(WindowsKey::Z)) {
		GameObject::SetPosition(XMFLOAT3(GameObject::GetPosition().x, GameObject::GetPosition().y + moveSpeed, GameObject::GetPosition().z));
	}
	if (InputHandler::KeyPressed(WindowsKey::X)) {
		GameObject::SetPosition(XMFLOAT3(GameObject::GetPosition().x, GameObject::GetPosition().y - moveSpeed, GameObject::GetPosition().z));
	}
	if (InputHandler::KeyPressed(WindowsKey::C)) {
		GameObject::SetRotation(XMFLOAT3(GameObject::GetRotation().x, GameObject::GetRotation().y - dt, GameObject::GetRotation().z));
	}
	if (InputHandler::KeyPressed(WindowsKey::V)) {
		GameObject::SetRotation(XMFLOAT3(GameObject::GetRotation().x, GameObject::GetRotation().y + dt, GameObject::GetRotation().z));
	}
	if (InputHandler::KeyPressed(WindowsKey::R)) {
		GameObject::SetRotation(XMFLOAT3(GameObject::GetRotation().x, GameObject::GetRotation().y, GameObject::GetRotation().z - dt));
	}
	if (InputHandler::KeyPressed(WindowsKey::F)) {
		GameObject::SetRotation(XMFLOAT3(GameObject::GetRotation().x, GameObject::GetRotation().y, GameObject::GetRotation().z + dt));
	}
	if (InputHandler::KeyPressed(WindowsKey::E)) {
		GameObject::SetRotation(XMFLOAT3(GameObject::GetRotation().x - dt, GameObject::GetRotation().y, GameObject::GetRotation().z));
	}
	if (InputHandler::KeyPressed(WindowsKey::Q)) {
		GameObject::SetRotation(XMFLOAT3(GameObject::GetRotation().x + dt, GameObject::GetRotation().y, GameObject::GetRotation().z));
	}
}
