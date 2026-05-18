#pragma once
#include "pch.h"

struct Transform
{
	glm::vec3 position = glm::vec3();
	glm::vec3 rotation = glm::vec3();
	glm::vec3 scale = glm::vec3(1.0f);
};

class GameObject
{
public:
	GameObject(const std::string& name = "");
	virtual ~GameObject() = default;

	virtual void Init() {}
	virtual void Start() {}
	virtual void Update(float dt) {}
	virtual void Render() {}
	virtual void Release() {}

	glm::mat4 GetModelMatrix() const {return modelMatrix; }
	void SetModelMatrix();

	void SetPosition(glm::vec3 position) { transform.position = position; SetModelMatrix(); }
	void SetRotation(glm::vec3 rotation) { transform.rotation = rotation; SetModelMatrix(); }
	void SetScale(glm::vec3 scale) { transform.scale = scale; SetModelMatrix(); }

protected:
	std::string name;

	Transform transform;
	glm::mat4 modelMatrix = glm::mat4(1.f);

};

