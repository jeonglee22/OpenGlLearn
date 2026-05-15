#pragma once
#include "pch.h"
#include "GameObject.h"
#include "Globals.h"

class Scene
{
public:
	Scene(SceneId sceneId);
	~Scene() = default;

	virtual void Init();
	virtual void Enter();
	virtual void Exit();
	virtual void Update(float dt);
	virtual void Render(GLFWwindow* window);
	virtual void Release();

	void AddGameObject(GameObject* go);
	void RemoveGameObject(GameObject* go = NULL);

private:
	SceneId sceneId;
	std::list<GameObject*> gameObjects;

};

