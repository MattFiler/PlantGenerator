#pragma once

#include "GameObject.h"

class ModelLoader : public GameObject
{
public:
	~ModelLoader() {
		Release();
	}

	void Create() override;
	void Release() override;
	void Update(float dt) override;
	void Render(float dt) override;

	void LoadModel(std::string path);

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