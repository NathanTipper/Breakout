#ifndef SPRITE_H
#define SPRITE_H

#include "Texture2D.h"
#include "glm/glm.hpp"
#include "shader.h"

struct Sprite
{
  Texture2D texture;
  glm::vec2 position;
  glm::vec2 size;
  glm::vec3 color;
  float rotation;
};

void sprite_generate_render_data();
void sprite_draw(Sprite* sprites, int count, ShaderProgram* sp);
void sprite_print(const Sprite* sprite);
#endif
