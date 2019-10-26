#pragma once

#include "dxutils.h"
#include "GameObjectManager.h"

class GameObject
{
public:
	GameObject() = default;
	~GameObject() {
		GameObjectManager::RemoveObject(this);
		Release();
	}

	virtual void Create();
	virtual void Release();
	virtual void Update(float dt);
	virtual void Render(float dt);

	virtual void SetRotation(XMFLOAT3 _rot)
	{
		rotation = _rot;
	}
	virtual XMFLOAT3 GetRotation()
	{
		return rotation;
	}

	virtual void SetPosition(XMFLOAT3 _pos)
	{
		position = _pos;
	}
	virtual XMFLOAT3 GetPosition()
	{
		return position;
	}
	
	virtual void SetScale(float _scale)
	{
		scale = XMFLOAT3(_scale, _scale, _scale);
	}
	virtual void SetScale(XMFLOAT3 _scale)
	{
		scale = _scale;
	}
	virtual XMFLOAT3 GetScale()
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

	void SetInvisible(bool _invis)
	{
		isInvisible = _invis;
	}
	bool GetInvisible()
	{
		return isInvisible;
	}

protected:
	XMMATRIX mWorld;

	XMFLOAT3 position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	bool isActive = true; //If false, won't render or update
	bool isInvisible = false; //If true, will update but not render

#ifdef _DEBUG
	ID3D11Buffer* GO_ConstantBuffer = nullptr;
	ID3D11Buffer* GO_VertexBuffer = nullptr;
	ID3D11Buffer* GO_IndexBuffer = nullptr;
	ID3D11VertexShader* GO_VertexShader = nullptr;
	ID3D11PixelShader* GO_PixelShader = nullptr;
	ID3D11InputLayout* GO_VertLayout = nullptr;
	int GO_VertCount = 0;
	int GO_IndexCount = 0;
#endif
};

