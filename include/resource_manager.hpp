#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

struct ShaderProgram;
struct Texture2D;

struct ResourceManager
{
    std::map<std::string, ShaderProgram> shaders;
    std::map<std::string, Texture2D> textures;
};

ShaderProgram ResourceManager_LoadShader(ResourceManager* rm, char* vShaderSource, char* fShaderSource, char* gShaderSource, std::string name);
ShaderProgram ResourceManager_GetShader(ResourceManager* rm, char* name);
Texture2D ResourceManager_LoadTexture(ResourceManager* rm, char* filename, bool alpha, std::string name);
Texture2D ResourceManager_GetTexture(ResourceManager* rm, std::string name);
void ResourceManager_Clear(ResourceManager* rm);

#endif
