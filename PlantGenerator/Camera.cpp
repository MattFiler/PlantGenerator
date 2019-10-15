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
}
