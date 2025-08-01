#include "ResourceManager/ResourceManager.hpp"
#include "Texture2D.h"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

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
        glDeleteProgram(iter.second.GetID());
    }

    for(auto iter : Textures)
    {
        unsigned int textureId = iter.second.GetId();
        glDeleteTextures(1, &textureId);
    }
}

ShaderProgram ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    ShaderProgram shader;

    shader.Init();
    shader.SetSource(SHADERTYPE_VERTEX, vShaderFile);
    shader.SetSource(SHADERTYPE_FRAGMENT, fShaderFile);
    shader.SetSource(SHADERTYPE_GEOMETRY, gShaderFile);

    shader.Compile();
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char *filename, bool alpha)
{
    Texture2D Result;

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename , &width, &height, &nrChannels, 0);

    if(data)
    {
        if(alpha)
        {
            Result.SetImageFormat(GL_RGBA);
            Result.SetInternalFormat(GL_RGBA);
        }
        else
        {
            if(nrChannels == 1)
            {
                Result.SetImageFormat(GL_RED);
                Result.SetInternalFormat(GL_RED);
            }
            else if(nrChannels == 2)
            {
                Result.SetImageFormat(GL_RGB);
                Result.SetInternalFormat(GL_RGB);
            }
            else if(nrChannels == 4)
            {
                Result.SetImageFormat(GL_RGBA);
                Result.SetInternalFormat(GL_RGBA);
            }
        }

        Result.Generate(width, height, data);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Could not open path: " << filename << std::endl;
    }

    return Result;
}
