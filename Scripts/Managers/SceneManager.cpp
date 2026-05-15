#include "SceneManager.h"

void SceneManager::Init()
{
	scenes.insert({ SceneId::Test, new Scene(SceneId::Test) });
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

void SceneManager::Render(GLFWwindow* window)
{
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scenes[currentScene]->Render(window);
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
