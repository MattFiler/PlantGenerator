#pragma once

#include "ModelPart.h"

class Model : public GameObject {
public:
	~Model() {
		Release();
	}

	void Create() override;
	void Release() override;
	void Update(float dt) override;
	void Render(float dt) override;

	int GetVertCount() {
		return vertexCount;
	}

	void SetRotation(XMFLOAT3 _rot) override
	{
		rotation = _rot;
		for (int i = 0; i < allModels.size(); i++) {
			allModels[i].SetRotation(rotation);
		}
	}

	void SetPosition(XMFLOAT3 _pos) override
	{
		position = _pos;
		for (int i = 0; i < allModels.size(); i++) {
			allModels[i].SetPosition(position);
		}
	}

	void SetScale(float _scale) override
	{
		scale = XMFLOAT3(_scale, _scale, _scale);
		for (int i = 0; i < allModels.size(); i++) {
			allModels[i].SetScale(scale);
		}
	}
	void SetScale(XMFLOAT3 _scale) override
	{
		scale = _scale;
		for (int i = 0; i < allModels.size(); i++) {
			allModels[i].SetScale(scale);
		}
	}

	void SetData(LoadedModel _m);

private:
	ID3D11Buffer* g_pVertexBuffer = nullptr;

	ID3D11SamplerState* g_pSamplerLinear = nullptr;
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11InputLayout* m_vertexLayout = nullptr;

	std::vector<ModelPart> allModels = std::vector<ModelPart>();
	std::vector<SimpleVertex> allVerts = std::vector<SimpleVertex>();

	int vertexCount = 0;
};