#pragma once

#include "dxutils.h"

class Cube
{
public:
	bool Create();
	bool Release();
	bool Update(float dt);
	bool Render(float dt);

protected:
	ID3D11Buffer* g_pVertexBuffer = nullptr;
	ID3D11Buffer* g_pIndexBuffer = nullptr;
	ID3D11Buffer* g_pConstantBuffer = nullptr;
	DirectX::XMMATRIX mWorld;

private:
	int vertexCount = 0;
	int indexCount = 0;
};