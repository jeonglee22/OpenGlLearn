#pragma once
#include "pch.h"
#include "GameObject.h"
#include "Globals.h"

class Scene
{
public:
	Scene(SceneId sceneId);
	virtual ~Scene() = default;

	virtual void Init();
	virtual void Enter();
	virtual void Exit();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Release();

	void AddGameObject(GameObject* go);
	void RemoveGameObject(GameObject* go = NULL);

protected:
	SceneId sceneId;
	std::list<GameObject*> gameObjects;

};

