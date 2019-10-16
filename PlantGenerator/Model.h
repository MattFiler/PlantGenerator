#pragma once

#include "GameObject.h"

class Model : public GameObject
{
public:
	~Model() {
		Release();
	}

	void Create() override;
	void Release() override;
	void Update(float dt) override;
	void Render(float dt) override;

	void SetData(LoadedModel _m) {
		modelMetaData = _m;
	}
	void SetData(std::vector<SimpleVertex> _vl, std::vector<WORD> _il, std::string _t)
	{
		modelMetaData.compVertices = _vl;
		modelMetaData.compIndices = _il;
		modelMetaData.textureName = _t;
	}

protected:
	ID3D11Buffer* g_pVertexBuffer = nullptr;
	ID3D11Buffer* g_pIndexBuffer = nullptr;

	ID3D11ShaderResourceView* g_pTextureRV = nullptr;
	ID3D11SamplerState* g_pSamplerLinear = nullptr;

	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11InputLayout* m_vertexLayout = nullptr;

	LoadedModel modelMetaData = LoadedModel();

private:
	int vertexCount = 0;
	int indexCount = 0;
};