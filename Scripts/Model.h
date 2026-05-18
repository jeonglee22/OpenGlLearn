#pragma once
#include "pch.h"
#include "Shader.h"
#include "Mesh.h"

using namespace std;

class Model
{
public:
    Model(const char *path)
    {
        loadModel(path);
    }
    void Draw(Shader &shader);	
private:
    // model data
    vector<Mesh> meshes;
    string directory;

    std::vector<TextureAssimp> textureLoaded;

    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<TextureAssimp> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                            string typeName);
};

