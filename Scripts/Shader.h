#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "pch.h"

class Shader
{
public:
    // the program ID
    unsigned int ID;
  
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader() { glDeleteProgram(ID); }

    // 복사 금지
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    // 이동 허용
    Shader(Shader&& other) noexcept : ID(other.ID) { other.ID = 0; }
    Shader& operator=(Shader&& other) noexcept {
        if (this != &other) {
            glDeleteProgram(ID);
            ID = other.ID;
            other.ID = 0;
        }
        return *this;
    }

    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};
  
#endif