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

	void SetRotation(XMFLOAT3 _rot)
	{
		rotation = _rot;
	}
	XMFLOAT3 GetRotation()
	{
		return rotation;
	}

	void SetPosition(XMFLOAT3 _pos)
	{
		position = _pos;
	}
	XMFLOAT3 GetPosition()
	{
		return position;
	}
	
	void SetScale(float _scale) 
	{
		scale = XMFLOAT3(_scale, _scale, _scale);
	}
	void SetScale(XMFLOAT3 _scale)
	{
		scale = _scale;
	}
	XMFLOAT3 GetScale()
	{
		return scale;
	}

	void SetActive(bool _active) 
	{
		isActive = _active;
	}
	bool GetActive() 
	{
		return isActive;
	}

protected:
	XMMATRIX mWorld;
	ID3D11Buffer* g_pConstantBuffer = nullptr;

	XMFLOAT3 position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	bool isActive = true;
};

