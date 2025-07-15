#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "Texture2D.h"
#include <string>

struct GameObject 
{
    glm::vec2 position, size, velocity;
    glm::vec3 color;
    float rotation;
    bool isSolid;
    bool isDestroyed;

    std::string textureName;
};
#endif
