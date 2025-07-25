#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H
#include "Texture2D.h"
#include "Shader.hpp"

#include "glad/glad.h"
#include "glm/glm.hpp"
#include <string>

class GameObject;

class SpriteRenderer
{
public:
        void Init();
        void DrawSprite(const Texture2D& texture, glm::vec2 position,
                        glm::vec2 size = glm::vec2(10.f, 10.f), float rotate = 0.f, glm::vec3 color = glm::vec3(1.f)) const;
        void DrawSprite(const GameObject& object);
        void DrawSprite(GameObject* object);

        void SetShader(std::string name);
private:
        ShaderProgram m_shader;
        unsigned int m_quadVAO;
};

#endif // SPRITERENDERER_H
