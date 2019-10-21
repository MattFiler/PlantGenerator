#pragma once

#include <vector>

class GameObject;

class GameObjectManager
{
public:
	GameObjectManager() {
		ClearObjects();
	}
	~GameObjectManager() {
		ClearObjects();
	}

	static void AddObject(GameObject* _aLight) {
		allGameObjects.push_back(_aLight);
	}
	static void RemoveObject(GameObject* _aLight) {
		for (int i = 0; i < allGameObjects.size(); i++) {
			if (allGameObjects[i] == _aLight) {
				allGameObjects.erase(allGameObjects.begin() + i);
			}
		}
	}

	static std::vector<GameObject*> GetObjects() {
		return allGameObjects;
	}
	static void ClearObjects() {
		allGameObjects.clear();
	}

	static void Create();
	static void Release();
	static void Update(float dt);
	static void Render(float dt);

private:
	static std::vector<GameObject*> allGameObjects;
};

