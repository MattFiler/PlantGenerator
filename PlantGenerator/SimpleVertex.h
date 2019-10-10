#pragma once
#include <DirectXMath.h>

struct SimpleVertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};

struct ConstantBuffer
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProjection;
};

struct Vector3
{
	Vector3(float _x, float _y, float _z) 
	{
		x = _x;
		y = _y;
		z = _z;
	}
	float x = 0;
	float y = 0;
	float z = 0;
};