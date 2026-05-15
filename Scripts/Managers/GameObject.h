#pragma once
#include "pch.h"

class GameObject
{
public:
	GameObject(const std::string& name = "");
	virtual ~GameObject() = default;

	virtual void Init() {}
	virtual void Start() {}
	virtual void Update(float dt) {}
	virtual void Render(GLFWwindow* window) {}
	virtual void Release() {}

protected:
	std::string name;

	glm::vec3 position = glm::vec3();
	glm::vec3 rotation = glm::vec3();
	glm::vec3 scale = glm::vec3(1.0f);

};

