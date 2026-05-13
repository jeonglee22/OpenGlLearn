#pragma once
#include "pch.h"

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

	void AddGameObject();
	void RemoveGameObject();

private:
	SceneId sceneId;

};

