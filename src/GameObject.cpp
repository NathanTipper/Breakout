#include "GameObject.hpp"
#include "SpriteRenderer/SpriteRenderer.hpp"

GameObject::GameObject()
    : m_color(glm::vec3(1.f))
    , m_isDestroyed(false)
    , m_isSolid(false)
    , m_rotation(0.f)
    , m_velocity(glm::vec2(0.f))
{ }

GameObject::GameObject(glm::vec2 position, glm::vec2 size, 
                       Texture2D sprite, glm::vec3 color, float rotation, glm::vec2 velocity)
    : m_position(position)
    , m_size(size)
    , m_texture(sprite)
    , m_color(color)
    , m_rotation(rotation)
    , m_velocity(velocity)
    , m_isDestroyed(false)
    , m_isSolid(false)
{ }

void GameObject::Draw(const SpriteRenderer& renderer)
{
    renderer.DrawSprite(m_texture, m_position, m_size, m_rotation, m_color);
}
