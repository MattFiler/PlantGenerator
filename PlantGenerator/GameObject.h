#pragma once

#include "dxutils.h"

class PointLight;

class GameObject
{
public:
	GameObject() = default;
	~GameObject() {
		Release();
	}

	virtual bool Create();
	virtual bool Release();
	virtual bool Update(float dt);
	virtual bool Render(float dt);

	void SetRotation(DirectX::XMFLOAT3 _rot)
	{
		rotation = _rot;
	}
	DirectX::XMFLOAT3 GetRotation()
	{
		return rotation;
	}

	void SetPosition(DirectX::XMFLOAT3 _pos)
	{
		position = _pos;
	}
	DirectX::XMFLOAT3 GetPosition()
	{
		return position;
	}

	void SetScale(DirectX::XMFLOAT3 _scale)
	{
		scale = _scale;
	}
	DirectX::XMFLOAT3 GetScale()
	{
		return scale;
	}

	void UseLight(PointLight* _light)
	{
		light = _light;
	}

protected:
	DirectX::XMMATRIX mWorld;
	ID3D11Buffer* g_pConstantBuffer = nullptr;

	DirectX::XMFLOAT3 position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);

	PointLight* light = nullptr;
};

