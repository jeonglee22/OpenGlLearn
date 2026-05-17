#pragma once
#include "pch.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

struct TextureAssimp{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureAssimp> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureAssimp> textures);

    void Draw(Shader &shader);

private:    
    //  render data
    VAO vao;
    VBO vbo;
    VBO ebo;

    void setupMesh();
};

