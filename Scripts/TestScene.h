#pragma once
#include "pch.h"
#include "Scene.h"

class TestScene :
    public Scene
{
public:
	TestScene(SceneId sceneId);
	~TestScene() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Render() override;
	void Release() override;
};

