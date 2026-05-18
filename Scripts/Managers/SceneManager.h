#pragma once
#include "pch.h"
#include "Scene.h"
#include "Globals.h"
#include "Singleton.h"

class SceneManager : public Singleton<SceneManager>
{
	friend Singleton<SceneManager>;

public:
	void Init();
	void Update(float dt);
	void Render();
	void Release();
	void LoadScene(SceneId nextScene);

	SceneId GetCurrentSceneId() const { return currentScene; }
	Scene* GetCurrnetScene() { return scenes[currentScene]; }

private:
	std::unordered_map<SceneId, Scene*> scenes;

	SceneId startScene = SceneId::Test;
	SceneId currentScene;
	SceneId changeScene = SceneId::None;

protected:
	SceneManager() = default;
	~SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
};

