#include "sprite.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "shader.h"
#include "glad/glad.h"
#include <iostream>

void sprite_generate_render_data(Sprite* sprite)
{
    if(!sprite)
    {
        std::cout << "SPRITE::GENERATE_RENDER_DATA : Invalid Sprite was given" << std::endl;
        return;
    }

    float vertices[] = {
        0.f, 1.f,   0.f, 1.f,
        1.f, 0.f,   1.f, 0.f,
        0.f, 0.f,   0.f, 0.f,

        0.f, 1.f,   0.f, 1.f,
        1.f, 1.f,   1.f, 1.f,
        1.f, 0.f,   1.f, 0.f
    };

    glGenVertexArrays(1, &sprite->VAO);
    glGenBuffers(1, &sprite->VBO);

    glBindBuffer(GL_ARRAY_BUFFER, sprite->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(sprite->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void sprite_draw(Sprite* sprites, int count, ShaderProgram* sp)
{
    if(!sp)
    {
        std::cout << "SPRITE::DRAW : Invalid Shader was provided" << std::endl;
        return; 
    }

    if(!sprites)
    {
        std::cout << "SPRITE::DRAW : Invalid Sprites were given" << std::endl;
        return;
    }

    shader_use(sp);

    glm::mat4 model = glm::mat4(1.f);

    for(int i = 0; i < count; ++i)
    {
        model = glm::translate(model, glm::vec3(sprites[i].position, 0.f));

        model = glm::translate(model, glm::vec3(0.5f * sprites[i].size.x, 0.5f * sprites[i].size.y, 0.f));
        model = glm::rotate(model, glm::radians(sprites[i].rotation), glm::vec3(0.f, 0.f, 1.f));
        model = glm::translate(model, glm::vec3(-0.5f * sprites[i].size.x, -0.5f * sprites[i].size.y, 0.f));

        model = glm::scale(model, glm::vec3(sprites[i].size, 1.f));

        shader_set_matrix(sp, (char*)"model", glm::value_ptr(model));
        shader_set_vec3(sp, (char*)"spriteColor", sprites[i].color.x, sprites[i].color.y, sprites[i].color.z);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sprites[i].texture.id);

        glBindVertexArray(sprites[i].VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}
