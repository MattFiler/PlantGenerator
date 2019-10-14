#pragma once

#include "dxutils.h"

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

	void SetRotation(Vector3 _rot);
	void SetPosition(Vector3 _pos);
	void SetScale(Vector3 _scale);

protected:
	DirectX::XMMATRIX mWorld;
	ID3D11Buffer* g_pConstantBuffer = nullptr;

	Vector3 position = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
};

