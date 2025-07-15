#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H
#include "Texture2D.h"
#include "shader.h"
#include "glm/glm.hpp"
class SpriteRenderer
{
	public:
        SpriteRenderer(ShaderProgram& shader);
        ~SpriteRenderer();

        void DrawSprite(Texture2D& texture, glm::vec2 position,
                        glm::vec2 size = glm::vec2(10.f, 10.f), float rotate = 0.f,
                        glm::vec3 color = glm::vec3(1.f));
	private:
        ShaderProgram m_shader;
        unsigned int m_quadVAO;

        void initRenderData();
};

#endif // SPRITERENDERER_H
