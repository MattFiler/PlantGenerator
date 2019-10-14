#pragma once

#include "GameObject.h"

class PointLight : public GameObject
{
public:
	~PointLight() {
		Release();
	}

	bool Create() override;
	bool Release() override;
	bool Update(float dt) override;
	bool Render(float dt) override;

	DirectX::XMFLOAT3 GetColour()
	{
		return lightColour;
	}
	void SetColour(DirectX::XMFLOAT3 colour)
	{
		lightColour = colour;
	}

private:
	DirectX::XMFLOAT3 lightColour = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
};

