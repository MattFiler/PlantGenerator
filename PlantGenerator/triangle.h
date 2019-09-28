#pragma once

#include "dxutils.h"

struct SimpleVertex
{
	DirectX::XMFLOAT3 Pos;  // Position
};

class Triangle
{
public:
	bool Create();
	bool Release();
	bool Render();

protected:
	ID3D11Buffer* g_pVertexBuffer = nullptr;
};