#pragma once

#include "GameObject.h"

class ModelPart : public GameObject
{
public:
	~ModelPart() {
		Release();
	}

	void Create() override;
	void Release() override;
	void Update(float dt) override;
	void Render(float dt) override;

	void SetData(LoadedModelPart _m) {
		modelMetaData = _m;
	}

protected:
	ID3D11Buffer* g_pVertexBuffer = nullptr;
	ID3D11Buffer* g_pIndexBuffer = nullptr;

	LoadedMaterial loadedMaterial = LoadedMaterial();
	ID3D11SamplerState* g_pSamplerLinear = nullptr;

	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11InputLayout* m_vertexLayout = nullptr;

	LoadedModelPart modelMetaData = LoadedModelPart();

private:
	int vertexCount = 0;
	int indexCount = 0;
};