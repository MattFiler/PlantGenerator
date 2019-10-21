#pragma once

#include <vector>

class GameObject;

class GameObjectManager
{
public:
	GameObjectManager() = default;
	~GameObjectManager() {
		Release();
	}

	static void AddObject(GameObject* _aLight) {
		allGameObjects.push_back(_aLight);
	}
	static void RemoveObject(GameObject* _aLight);

	static void Create();
	static void Release();
	static void Update(float dt);
	static void Render(float dt);

private:
	static std::vector<GameObject*> allGameObjects;
};

