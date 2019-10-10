#pragma once

#include "dxutils.h"

class Cube
{
public:
	~Cube() {
		Release();
	}

	bool Create();
	bool Release();
	bool Update(float dt);
	bool Render(float dt);

	void SetRotation(Vector3 _rot);
	void SetPosition(Vector3 _pos);
	void SetScale(Vector3 _scale);

protected:
	ID3D11Buffer* g_pVertexBuffer = nullptr;
	ID3D11Buffer* g_pIndexBuffer = nullptr;
	ID3D11Buffer* g_pConstantBuffer = nullptr;
	DirectX::XMMATRIX mWorld;

private:
	int vertexCount = 0;
	int indexCount = 0;

	//Transforms
	Vector3 position = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
};