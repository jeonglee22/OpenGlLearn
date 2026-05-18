#include "GameObject.h"

GameObject::GameObject(const std::string& name)
	: name(name)
{
}

void GameObject::SetModelMatrix()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, transform.position);
	model = glm::rotate(model, transform.rotation.x, glm::vec3(1.f, 0.f, 0.f));
	model = glm::rotate(model, transform.rotation.y, glm::vec3(0.f, 1.f, 0.f));
	model = glm::rotate(model, transform.rotation.z, glm::vec3(0.f, 0.f, 1.f));
	model = glm::scale(model, transform.scale);

	modelMatrix = model;
}

