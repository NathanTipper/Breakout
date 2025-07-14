#include "shader.h"
#include <glad/glad.h>
#include <cstdio>
#include <iostream>
#include "utils.h"

void shader_init(ShaderProgram* sp)
{
    sp->id = glCreateProgram();
    for(int i = 0; i < SHADERTYPE_COUNT; ++i)
    {
        sp->shaders[i] = 0;
        sp->shader_source[i][0] = '\0';
    }
}

bool shader_link(ShaderProgram* sp)
{
    for(int i = 0; i < SHADERTYPE_COUNT; ++i)
    {
        if(sp->shaders[i])
        {
            glAttachShader(sp->id, sp->shaders[i]);
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

    glLinkProgram(sp->id);
    int success;
    char infoLog[512];
    glGetProgramiv(sp->id, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(sp->id, 512, NULL, infoLog);
        printf("Shader Program linking failed: %s\n", infoLog);
        return false;
    }

    for(int i = 0; i < SHADERTYPE_COUNT; ++i)
    {
        if(sp->shaders[i])
        {
            glDeleteShader(sp->shaders[i]);
            sp->shaders[i] = 0;
        }
    }

    return true;
}

void shader_use(ShaderProgram* sp)
{
    glUseProgram(sp->id);
}

void shader_set_float(ShaderProgram* sp, char* name, float value)
{
    unsigned int uniformLocation = glGetUniformLocation(sp->id, name);
    glUniform1f(uniformLocation, value);
}

void shader_set_int(ShaderProgram* sp, char* name, int value)
{
    unsigned int uniformLocation = glGetUniformLocation(sp->id, name);
    glUniform1i(uniformLocation, value);
}

void shader_set_matrix(ShaderProgram *sp, char *name, float* value)
{
    unsigned int uniformLocation = glGetUniformLocation(sp->id, name);

    if(uniformLocation)
    {
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value);
    }
    else
    {
        std::cout << "Could not find uniform location" << std::endl;
    }
}

void shader_set_vec3(ShaderProgram *sp, char *name, float v0, float v1, float v2)
{
    unsigned int uniformLocation = glGetUniformLocation(sp->id, name);
    glUniform3f(uniformLocation, v0, v1, v2);
}

void shader_set_source(ShaderProgram* sp, ShaderType st, const char *filename)
{
    char const *c = filename;
    int stringIndex = 0;
    while(*c != 0)
    {
        if(stringIndex >= SHADER_SOURCE_FILENAME_SIZE)
        {
            printf("Shader source filename exceeded max character count!");
            for(int i = 0; i < SHADER_SOURCE_FILENAME_SIZE; ++i)
            {
                sp->shader_source[st][i] = 0;
            }
            return;
        }

        sp->shader_source[st][stringIndex++] = *c++;
    }
    sp->shader_source[st][stringIndex] = '\0';
}

bool shader_load(ShaderProgram* sp)
{
    for(int i = 0; i < SHADERTYPE_COUNT; ++i)
    {
        if(stringLength(sp->shader_source[i]) == 0)
        {
            continue;
        }

        Win32ReadFileResult rfr = win32ReadFile(sp->shader_source[i]);
        if(!rfr.contents || !rfr.filesize)
        {
            printf("Could not read file %s", sp->shader_source[i]);
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
                printf("Could not find valid shader type");
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

        sp->shaders[i] = shader;
        win32Free(rfr.contents, rfr.filesize);
    }

    return true;
}

void shader_delete(ShaderProgram* sp)
{
    glDeleteProgram(sp->id);
}
