#include "GameObject.h"

/* Set the GameObject's position */
void GameObject::SetPosition(Vector3 _pos)
{
	position = _pos;
}

/* Set the GameObject's rotation */
void GameObject::SetRotation(Vector3 _rot)
{
	rotation = _rot;
}

/* Set the GameObject's scale */
void GameObject::SetScale(Vector3 _scale)
{
	scale = _scale;
}

/* Create our low level GameObject resources */
bool GameObject::Create()
{
	//Create the constant buffer 
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	HR(dxshared::m_pDevice->CreateBuffer(&bd, nullptr, &g_pConstantBuffer));

	//Initialize the world matrix 
	mWorld = DirectX::XMMatrixIdentity();

	return true;
}

/* Safely release our low level GameObject memory */
bool GameObject::Release()
{
	Memory::SafeRelease(g_pConstantBuffer);
	return false;
}

/* Perform low level GameObject update functions */
bool GameObject::Update(float dt) 
{
	//Set the cube's world based on translations (todo: X rotation)
	mWorld = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) * DirectX::XMMatrixRotationZ(rotation.z) * DirectX::XMMatrixTranslation(position.x, position.y, position.z) * DirectX::XMMatrixRotationY(rotation.y);

	return true;
}

/* Perform low level GameObject render functions */
bool GameObject::Render(float dt) 
{
	//Update and set constant buffer
	ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(mWorld);
	cb.mView = XMMatrixTranspose(dxshared::mView);
	cb.mProjection = XMMatrixTranspose(dxshared::mProjection);
	dxshared::m_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	dxshared::m_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);

	return true;
}