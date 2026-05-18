#include "SceneManager.h"
#include "TestScene.h"

void SceneManager::Init()
{
	scenes.insert({ SceneId::Test, new TestScene(SceneId::Test) });
	scenes.insert({ SceneId::Start, new Scene(SceneId::Start) });

	for (auto scene : scenes)
	{
		scene.second->Init();
	}

	currentScene = startScene;
	scenes[currentScene]->Enter();
}

void SceneManager::Update(float dt)
{
	if (changeScene != SceneId::None)
	{
		scenes[currentScene]->Exit();
		currentScene = changeScene;
		changeScene = SceneId::None;
		scenes[currentScene]->Enter();
	}

	scenes[currentScene]->Update(dt);
}

void SceneManager::Render()
{
	scenes[currentScene]->Render();
}

void SceneManager::Release()
{
	scenes[currentScene]->Exit();
	for (auto scene : scenes)
	{
		scene.second->Release();
		delete scene.second;
	}

	scenes.clear();
}

void SceneManager::LoadScene(SceneId nextScene)
{
	changeScene = nextScene;
}
