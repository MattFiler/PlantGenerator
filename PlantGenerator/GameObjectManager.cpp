#include "GameObjectManager.h"
#include "GameObject.h"

std::vector<GameObject*> GameObjectManager::allGameObjects = std::vector<GameObject*>();

void GameObjectManager::Create()
{
	for (int i = 0; i < allGameObjects.size(); i++) {
		allGameObjects[i]->Create();
	}
}

void GameObjectManager::Release()
{
	for (int i = 0; i < allGameObjects.size(); i++) {
		allGameObjects[i]->Release();
	}
}

void GameObjectManager::Update(float dt)
{
	for (int i = 0; i < allGameObjects.size(); i++) {
		allGameObjects[i]->Update(dt);
	}
}

void GameObjectManager::Render(float dt)
{
	for (int i = 0; i < allGameObjects.size(); i++) {
		allGameObjects[i]->Render(dt);
	}
}
