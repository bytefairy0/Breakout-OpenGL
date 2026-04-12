#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
using namespace std;

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"

class ResourceManager{
public:
    static map<std::string, Shader>    Shaders;
    static map<std::string, Texture2D> Textures;

    // loads ( shader program from file 
    static Shader    LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    // retrieves a stored sader
    static Shader    GetShader(std::string name);

    // loads texture from file
    static Texture2D LoadTexture(const char *file, bool alpha, std::string name);
    // retrieves a stored texture
    static Texture2D GetTexture(std::string name);

    static void      Clear();

private:
    ResourceManager() { }
    static Shader    loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
    static Texture2D loadTextureFromFile(const char *file, bool alpha);
};

#endif