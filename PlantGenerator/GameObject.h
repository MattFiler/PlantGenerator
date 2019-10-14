#pragma once

#include "dxutils.h"

class GameObject
{
public:
	GameObject() = default;
	~GameObject() {
		Release();
	}

	virtual void Create();
	virtual void Release();
	virtual void Update(float dt);
	virtual void Render(float dt);

	void SetRotation(XMFLOAT3 _rot);
	void SetPosition(XMFLOAT3 _pos);
	void SetScale(XMFLOAT3 _scale);

protected:
	XMMATRIX mWorld;
	ID3D11Buffer* g_pConstantBuffer = nullptr;

	XMFLOAT3 position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
};

