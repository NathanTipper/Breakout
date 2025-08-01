#include "SpriteRenderer/SpriteRenderer.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GameObject.hpp"

void SpriteRenderer::Init()
{
    float vertices[] = {
        0.f, 1.f,   0.f, 1.f,
        1.f, 0.f,   1.f, 0.f,
        0.f, 0.f,   0.f, 0.f,

        0.f, 1.f,   0.f, 1.f,
        1.f, 1.f,   1.f, 1.f,
        1.f, 0.f,   1.f, 0.f
    };

    glGenVertexArrays(1, &m_quadVAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(m_quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(const Texture2D& texture, glm::vec2 position, 
                                glm::vec2 size, float rotation, glm::vec3 color) const
{
    m_shader.Use();
    glm::mat4 model;
    glBindVertexArray(m_quadVAO);
    glActiveTexture(GL_TEXTURE0);

    model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(position, 0.f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));

    model = glm::scale(model, glm::vec3(size, 1.f));

    m_shader.SetMatrix("model", glm::value_ptr(model));
    m_shader.SetVec3("spriteColor", color);
    texture.Bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(const GameObject& object)
{
    DrawSprite(object.GetTexture(), object.GetPosition(), object.GetSize(), object.GetRotation(), object.GetColor());
}

void SpriteRenderer::SetShader(std::string name)
{
    m_shader = ResourceManager::GetShader(name);
}

void SpriteRenderer::DrawSprite(GameObject* object)
{
    if(object)
    {
        DrawSprite(*object);
    }
}
