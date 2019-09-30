#pragma once

#include "dxutils.h"

class Cube
{
public:
	bool Create();
	bool Release();
	bool Render();

protected:
	ID3D11Buffer* g_pVertexBuffer = nullptr;
	ID3D11Buffer* g_pIndexBuffer = nullptr;
	ID3D11Buffer* g_pConstantBuffer = nullptr;
	ConstantBuffer m_cBufferObj = ConstantBuffer();
};