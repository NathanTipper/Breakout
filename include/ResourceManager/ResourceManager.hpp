#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "Texture2D.h"
#include "Shader.hpp"
#include <map>
#include <string>
class ResourceManager
{
	public:
        static std::map<std::string, ShaderProgram> Shaders;
        static std::map<std::string, Texture2D> Textures;
        static ShaderProgram LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
        static ShaderProgram GetShader(std::string name);

        static Texture2D LoadTexture(const char *file, bool alpha, std::string name);
        static Texture2D GetTexture(std::string name);

        static void Clear();
    private:
        ResourceManager() { }

        static ShaderProgram loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
        static Texture2D loadTextureFromFile(const char *file, bool alpha);
};

#endif // RESOURCEMANAGER_H
