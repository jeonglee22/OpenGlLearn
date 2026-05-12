#pragma once

#include "pch.h"

enum TextureType {
    DIFFUSE,
    SPECULAR,
    NORMAL,
    HEIGHT
};

enum TextureWrapMode {
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER
};

enum TextureFilterMode {
    NEAREST,
    LINEAR,
    NEAREST_MIPMAP_NEAREST,
    LINEAR_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR_MIPMAP_LINEAR
};

enum TextureFormat {
    RGB,
    RGBA,
    RED,
    DEPTH_COMPONENT
};

enum TextureDataType {
    UNSIGNED_BYTE,
    FLOAT,
    UNSIGNED_INT,
    BYTE,
    INT
};

class Texture
{
public:
    unsigned int ID;
    TextureType type;
    std::string path;
    TextureWrapMode wrapS;
    TextureWrapMode wrapT;
    TextureFilterMode minFilter;
    TextureFilterMode magFilter;
    TextureFormat format;
    TextureDataType dataType;

    // Texture(const char* path, TextureDataType dataType);
    Texture(const char* path, TextureDataType dataType, TextureWrapMode wrapS = REPEAT, TextureWrapMode wrapT = REPEAT, TextureFilterMode minFilter = LINEAR_MIPMAP_LINEAR, TextureFilterMode magFilter = LINEAR);
    ~Texture();
private:
    void SetTextureParameters(TextureDataType dataType, TextureWrapMode wrapS, TextureWrapMode wrapT, TextureFilterMode minFilter, TextureFilterMode magFilter);

public:
    void Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, ID);
    }
};
