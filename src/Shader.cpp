#include "Shader.hpp"
#include <glad/glad.h>
#include <cstdio>
#include <iostream>
#include "utils.h"

ShaderProgram::ShaderProgram()
{
}

void ShaderProgram::Init()
{
    m_id = glCreateProgram();
    for(int i = 0; i < SHADERTYPE_COUNT; ++i)
    {
        shaders[i] = 0;
        shader_source[i][0] = '\0';
    }
}

void ShaderProgram::Use() const
{
    glUseProgram(m_id);
}

bool ShaderProgram::Compile()
{
    for(int i = 0; i < SHADERTYPE_COUNT; ++i)
    {
        if(stringLength(shader_source[i]) == 0)
        {
            continue;
        }

        Win32ReadFileResult rfr = win32ReadFile(shader_source[i]);
        if(!rfr.contents || !rfr.filesize)
        {
            printf("Could not read file %s", shader_source[i]);
            return false;
        }

        GLenum glShaderType;
        switch(i)
        {
            case 0:
                glShaderType = GL_VERTEX_SHADER;
                break;
            case 1:
                glShaderType = GL_FRAGMENT_SHADER;
                break;
            case 2:
                glShaderType = GL_GEOMETRY_SHADER;
                break;
            default:
                printf("Could not find valm_id shader type");
                return false;
        }

        unsigned int shader;
        shader = glCreateShader(glShaderType);
        char* stringBuffer = (char*)rfr.contents;
        glShaderSource(shader, 1, &stringBuffer, 0);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 512, 0, infoLog);
            // Log some info
            printf("Vertex Shader compilation failed: %s\n", infoLog);
            return false;
        }

        shaders[i] = shader;
        win32Free(rfr.contents, rfr.filesize);
    }

    for(int i = 0; i < SHADERTYPE_COUNT; ++i)
    {
        if(shaders[i])
        {
            glAttachShader(m_id, shaders[i]);
        }
        else
        {
            if(i <= SHADERTYPE_FRAGMENT)
            {
                printf("Could not link! Must have at least a vertex and fragment shader!");
                return false;
            }
        }
    }

    glLinkProgram(m_id);
    int success;
    char infoLog[512];
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        printf("Shader Program linking failed: %s\n", infoLog);
        return false;
    }

    for(int i = 0; i < SHADERTYPE_COUNT; ++i)
    {
        if(shaders[i])
        {
            glDeleteShader(shaders[i]);
            shaders[i] = 0;
        }
    }

    return true;
}

void ShaderProgram::SetFloat(const char* name, const float value) const
{
    unsigned int uniformLocation = GetUniformLocation(name);
    glUniform1f(uniformLocation, value);
}

void ShaderProgram::SetInt(const char* name, const int value) const
{
    unsigned int uniformLocation = GetUniformLocation(name);
    glUniform1i(uniformLocation, value);
}

void ShaderProgram::SetMatrix(const char* name, const float* value) const
{
    unsigned int uniformLocation = GetUniformLocation(name);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value);
}

void ShaderProgram::SetVec3(const char* name, const glm::vec3 value) const
{
    unsigned int uniformLocation = GetUniformLocation(name);
    glUniform3f(uniformLocation, value.x, value.y, value.z);
}

void ShaderProgram::SetSource(ShaderType type, const char* filename)
{
    if(!filename)
    {
        return;
    }

    char const *c = filename;
    int stringIndex = 0;
    while(*c != 0)
    {
        if(stringIndex >= SHADER_SOURCE_FILENAME_SIZE)
        {
            printf("Shader source filename exceeded max character count!");
            for(int i = 0; i < SHADER_SOURCE_FILENAME_SIZE; ++i)
            {
                shader_source[type][i] = 0;
            }
            return;
        }

        shader_source[type][stringIndex++] = *c++;
    }
    shader_source[type][stringIndex] = '\0';
}

void ShaderProgram::Delete() const
{
    glDeleteProgram(m_id);
}

unsigned int ShaderProgram::GetUniformLocation(const char* name) const
{
    unsigned int Result = glGetUniformLocation(m_id, name);
    if(Result < 0)
    {
        std::cout << "ShaderProgram::GetUniformLocation : Could not find uniform with name " << name << std::endl;
    }

    return Result;
}
