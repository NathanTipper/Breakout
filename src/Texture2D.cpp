#include "Texture2D.h"
#include "glad/glad.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void generate_Texture2D(Texture2D *texture, unsigned char *data)
{
    if(!texture)
    {
        return;
    }

    glGenTextures(1, &texture->id);

    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexImage2D(GL_TEXTURE_2D, 0, texture->internal_format, texture->width, texture->height, 0, 
                    texture->image_format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture->filter_max);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D texture2D_load_from_file(const char *filename)
{
    Texture2D Result;

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

    if(data)
    {
        if(nrChannels == 1)
        {
            Result.image_format = GL_RED;
            Result.internal_format = GL_RED;
        }
        else if(nrChannels == 2)
        {
            Result.image_format = GL_RGB;
            Result.internal_format = GL_RGB;
        }
        else if(nrChannels == 4)
        {
            Result.image_format = GL_RGBA;
            Result.internal_format = GL_RGBA;
        }
        else 
        {
            Result.image_format = GL_RGB;
            Result.internal_format = GL_RGB;
        }

        Result.width = width;
        Result.height = height;
        Result.wrap_s = GL_REPEAT;
        Result.wrap_t = GL_REPEAT;
        Result.filter_min = GL_LINEAR;
        Result.filter_max = GL_LINEAR;

        generate_Texture2D(&Result, data);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Could not open path: " << filename << std::endl;
    }

    return Result;
}

void bind_Texture2D(Texture2D *texture)
{
    if(texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture->id);
    }
}
