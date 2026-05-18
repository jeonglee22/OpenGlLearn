#include "TestScene.h"
#include "ModelObject.h"
#include "filesystem.h"
#include "ShaderManager.h"

TestScene::TestScene(SceneId sceneId)
    : Scene(sceneId)
{
}

void TestScene::Init()
{
    Shader* modelShader = ShaderManager::GetInstance().Get("Model");
    ModelObject* model1 = new ModelObject(FileSystem::getPath("Assets/Models/backpack/backpack.obj").c_str(), modelShader);
    AddGameObject(model1);

    Scene::Init();
}

void TestScene::Enter()
{
    Scene::Enter();
}

void TestScene::Exit()
{
    Scene::Exit();
}

void TestScene::Update(float dt)
{
    Scene::Update(dt);   
}

void TestScene::Render()
{
    Scene::Render();
}

void TestScene::Release()
{
    Scene::Release();
}
