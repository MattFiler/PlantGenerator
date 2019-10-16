#include "GameObject.h"

/* Create our low level GameObject resources */
void GameObject::Create()
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
	mWorld = XMMatrixIdentity();
}

/* Safely release our low level GameObject memory */
void GameObject::Release()
{
	Memory::SafeRelease(g_pConstantBuffer);
}

/* Perform low level GameObject update functions */
void GameObject::Update(float dt)
{
	if (!isActive) return;
	mWorld = XMMatrixScaling(scale.x, scale.y, scale.z) * XMMatrixTranslation(position.x, position.y, position.z) * XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
}

/* Perform low level GameObject render functions */
void GameObject::Render(float dt)
{
	//Update and set constant buffer
	ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(mWorld);
	cb.mView = XMMatrixTranspose(dxshared::mView);
	cb.mProjection = XMMatrixTranspose(dxshared::mProjection);
	dxshared::m_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	dxshared::m_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
}