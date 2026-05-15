#pragma once
#include "pch.h"
#include "Shader.h"
#include "Singleton.h"

class ShaderManager : public Singleton<ShaderManager> 
{
    friend Singleton<ShaderManager>;

protected:
    ShaderManager() = default;
    ~ShaderManager() override = default;
    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;

public:
    void Load(const std::string& name, const char* vertPath, const char* fragPath);
    Shader* Get(const std::string& name);

    void Init();
    void Release();

private:
    std::unordered_map<std::string, Shader> shaders;
};

