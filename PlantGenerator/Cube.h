#pragma once

#include "dxutils.h"
#include "GameObject.h"

class Cube : public GameObject
{
public:
	~Cube() {
		Release();
	}

	bool Create() override;
	bool Release() override;
	bool Update(float dt) override;
	bool Render(float dt) override;

protected:
	ID3D11Buffer* g_pVertexBuffer = nullptr;
	ID3D11Buffer* g_pIndexBuffer = nullptr;

	ID3D11ShaderResourceView* g_pTextureRV = nullptr;
	ID3D11SamplerState* g_pSamplerLinear = nullptr;

	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11InputLayout* m_vertexLayout = nullptr;

private:
	int vertexCount = 0;
	int indexCount = 0;
};