#pragma once

#include "dxmain.h"
#include "TestScene.h"
#include "TestScene2.h"

class Scene;

class SceneManager : public dxmain
{
public:
	SceneManager(HINSTANCE hInstance) : dxmain(hInstance) {};
	~SceneManager();

	bool Init() override;
	bool Update(double dt) override;
	void Render(double dt) override;

	void ChangeScene(int _newScene) 
	{
		if (requestedSceneIndex == _newScene) return;
		Debug::Log("Switching to scene: " + std::to_string(_newScene));
		requestedSceneIndex = _newScene;
	}
	void AddScene(Scene* _newScene)
	{
		Debug::Log("Adding scene!");
		availableScenes.push_back(_newScene);
		Debug::Log("Scene count is now: " + std::to_string(availableScenes.size()));
	}

private:
	int requestedSceneIndex = -1;
	int currentSceneIndex = -1;
	std::vector<Scene*> availableScenes = std::vector<Scene*>();

	TestScene newScene = TestScene();
	TestScene2 newScene2 = TestScene2();
};

