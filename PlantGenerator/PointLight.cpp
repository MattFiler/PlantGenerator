#include "PointLight.h"


bool PointLight::Create()
{
	SetPosition(DirectX::XMFLOAT3(100000.0f, 100000.0f, 100000.0f));
	SetColour(DirectX::XMFLOAT3(150.5f, 0.5f, 0.5f));
	return false;
}

bool PointLight::Release()
{
	return false;
}

bool PointLight::Update(float dt)
{
	return false;
}

bool PointLight::Render(float dt)
{
	return false;
}