#include "ModelPart.h"
#include "Light.h"
#include <fstream>
#include <vector>

/* Create basic resources */
void ModelPart::Create()
{
	GameObject::Create();

	//Create index buffer 
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	indexCount = modelMetaData.compIndices.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * indexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = modelMetaData.compIndices.data();
	HR(dxshared::m_pDevice->CreateBuffer(&bd, &InitData, &g_pIndexBuffer));

	//Create the constant buffer 
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	HR(dxshared::m_pDevice->CreateBuffer(&bd, nullptr, &g_pConstantBuffer));

	//Setup material
	loadedMaterial.materialName = modelMetaData.thisMaterial.materialName;

	//Load texture file
	ID3D11ShaderResourceView* newTex;
	std::wstring widestr = std::wstring(modelMetaData.thisMaterial.texturePath.begin(), modelMetaData.thisMaterial.texturePath.end());
	HR(CreateDDSTextureFromFile(dxshared::m_pDevice, widestr.c_str(), nullptr, &newTex));
	loadedMaterial.materialTexture = newTex;

	//Populate colour data
	loadedMaterial.materialColour.x = modelMetaData.thisMaterial.r;
	loadedMaterial.materialColour.y = modelMetaData.thisMaterial.g;
	loadedMaterial.materialColour.z = modelMetaData.thisMaterial.b;
	loadedMaterial.materialColour.w = modelMetaData.thisMaterial.a;
}

/* Release the model */
void ModelPart::Release()
{
	GameObject::Release();

	Memory::SafeRelease(g_pIndexBuffer);
	Memory::SafeRelease(loadedMaterial.materialTexture);
	Memory::SafeRelease(g_pConstantBuffer);
}

/* Update the model */
void ModelPart::Update(float dt)
{
	GameObject::Update(dt);

	if (!isActive) return;
	if (indexCount == 0) return;
}

/* Render the model */
void ModelPart::Render(float dt)
{
	//GameObject::Render(dt);

	if (!isActive) return;
	if (indexCount == 0) return;

	//Update and set constant buffer
	ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose(mWorld);
	cb.mView = XMMatrixTranspose(dxshared::mView);
	cb.mProjection = XMMatrixTranspose(dxshared::mProjection);
	cb.colourTint = loadedMaterial.materialColour;
	//cb.numOfLights = (LightManager::GetLightCount() > 10) ? 10 : LightManager::GetLightCount();
	//for (int i = 0; i < 10; i++) {
		//if (i >= LightManager::GetLightCount()) break;
		XMFLOAT3 pos = GameObjectManager::GetLights()[0]->GetPosition();
		cb.pointlightPosition = XMFLOAT4(pos.x, pos.y, pos.z, GameObjectManager::GetLights()[0]->GetIntensity());
		cb.pointlightColour = GameObjectManager::GetLights()[0]->GetColour();
	//}
	cb.ambientLight = dxshared::ambientLightColour;
	dxshared::m_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	dxshared::m_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	dxshared::m_pImmediateContext->PSSetConstantBuffers(0, 1, &g_pConstantBuffer);

	//Set texture
	dxshared::m_pImmediateContext->PSSetShaderResources(0, 1, &loadedMaterial.materialTexture);

	//Set index buffer and draw
	dxshared::m_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	dxshared::m_pImmediateContext->DrawIndexed(indexCount, 0, 0);
}
