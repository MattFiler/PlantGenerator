#pragma once

#include "dxutils.h"

struct SimpleVertex
{
	DirectX::XMFLOAT3 Pos;  // Position
};

class Triangle
{
public:
	void Create();

protected:
	ID3D11Buffer*           g_pVertexBuffer = nullptr;
};