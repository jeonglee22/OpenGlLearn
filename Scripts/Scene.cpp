#include "Scene.h"


Scene::Scene(SceneId sceneId)
	: sceneId(sceneId)
{
}

void Scene::Init() {
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void Scene::Enter() {
	for (auto go : gameObjects)
	{
		go->Start();
	}
}

void Scene::Exit() {
	
}

void Scene::Update(float dt) {
	for (auto go : gameObjects)
	{
		go->Update(dt);
	}
}

void Scene::Render() {
	for (auto go : gameObjects)
	{
		go->Render();
	}
}

void Scene::Release() {
	for (auto go : gameObjects)
	{
		go->Release();
	}
}

void Scene::AddGameObject(GameObject* go) {
	gameObjects.push_back(go);
}

void Scene::RemoveGameObject(GameObject* go) {
	if (go != NULL)
		gameObjects.remove(go);
	else
		gameObjects.pop_back();
}