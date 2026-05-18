#include "ShaderManager.h"

void ShaderManager::Load(const std::string& name, const char* vertPath, const char* fragPath) {
	shaders.emplace(name, Shader(vertPath, fragPath));
}

Shader* ShaderManager::Get(const std::string& name) {
	auto iter = shaders.find(name);
	if (iter != shaders.end())
		return &iter->second;
	else
		return nullptr;
}

void ShaderManager::Init() {
	Load("Base", "Scripts/Shaders/ex1.vs", "Scripts/Shaders/ex1.fs");
	Load("Light", "Scripts/Shaders/light.vs", "Scripts/Shaders/light.fs");
	Load("Cube", "Scripts/Shaders/object.vs", "Scripts/Shaders/object.fs");
	Load("Model", "Scripts/Shaders/model.vs", "Scripts/Shaders/model.fs");
}

void ShaderManager::Release() {
	shaders.clear();
}