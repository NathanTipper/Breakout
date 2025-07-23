#include "GameObject.hpp"
#include "SpriteRenderer/SpriteRenderer.hpp"

GameObject::GameObject()
{ }

GameObject::GameObject(glm::vec2 position, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
    : m_position(position)
    , m_size(size)
    , m_texture(sprite)
    , m_color(color)
    , m_velocity(velocity)
{ }

void GameObject::Draw(SpriteRenderer* renderer)
{
    if(!renderer)
    {
        return;
    }
    renderer->DrawSprite(m_texture, m_position, m_size, m_rotation, m_color);
}
