#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "Shader.hpp"

class PostProcessor
{
public:
    ShaderProgram PostProcessingShaderProgram;
    Texture2D Texture;
    unsigned int Width, Height;
    bool Confuse, Chaos, Shake;
    PostProcessor();
	void Init(ShaderProgram shader, unsigned int width, unsigned int height);
    void BeginRender();
    void EndRender();
    void Render(float time);
private:
    unsigned int MSFBO, FBO; // MSFBO = Multisampled FBO. FBO is regular, used for blitting MS color-buffer to texture
    unsigned int RBO; // RBO is used for multisampled color buffer
    unsigned int VAO;
    void initRenderData();
};

#endif // POSTPROCESSOR_H
