#pragma once
#include "pch.h"
#include "GameObject.h"
#include "Model.h"

class ModelObject :
    public GameObject
{
public:
    ModelObject(const char* path, Shader* shader);

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    void Release() override;
private:
    Model* model;
    Shader* shader;

    float angleSpeed = 10.f;
};

