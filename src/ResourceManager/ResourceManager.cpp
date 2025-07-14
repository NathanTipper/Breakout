#include "ResourceManager/ResourceManager.hpp"
#include "Texture2D.h"
#include "shader.h"
#include <glad/glad.h>

std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, ShaderProgram> ResourceManager::Shaders;

ShaderProgram ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

ShaderProgram ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char *file, bool alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    for(auto iter : Shaders)
    {
        glDeleteProgram(iter.second.id);
    }

    for(auto iter : Textures)
    {
        glDeleteTextures(1, &iter.second.id);
    }
}

ShaderProgram ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    ShaderProgram shader;

    shader_init(&shader);
    shader_set_source(&shader, SHADERTYPE_VERTEX, vShaderFile);
    shader_set_source(&shader, SHADERTYPE_FRAGMENT, fShaderFile);
    shader_set_source(&shader, SHADERTYPE_GEOMETRY, gShaderFile);

    shader_link(&shader);
    shader_load(&shader);

    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
    return texture2D_load_from_file(file);
}
