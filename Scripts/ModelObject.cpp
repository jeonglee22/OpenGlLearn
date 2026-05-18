#include "ModelObject.h"

ModelObject::ModelObject(const char *path, Shader *shader)
    : shader(shader)
{
    model = new Model(path);
}

void ModelObject::Start()
{
}

void ModelObject::Update(float dt)
{
    float currentAngle = transform.rotation.y;
    float nextAngle = currentAngle + dt * angleSpeed;

    glm::vec3 rotation = glm::vec3(0.f, nextAngle, 0.f);
    SetRotation(rotation);
}

void ModelObject::Render()
{
    shader->use();
    shader->setMat4("model", modelMatrix);
    model->Draw(*shader);
}

void ModelObject::Release()
{
    delete(model);
}
