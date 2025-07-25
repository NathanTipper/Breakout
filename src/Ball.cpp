#include "Ball.hpp"

Ball::Ball() 
    : GameObject()
    , m_radius(DEFAULT_BALL_RADIUS)
    , m_stuck(true)
{ 
    m_size = glm::vec2(m_radius * 2.f, m_radius * 2.f);
}

Ball::Ball(glm::vec2 position, Texture2D texture, float radius, glm::vec3 color, float rotation, glm::vec2 velocity)
    : GameObject(position, glm::vec2(radius * 2.f, radius * 2.f), texture, color, rotation, velocity)
    , m_radius(radius)
    , m_stuck(true)
{ }

glm::vec2 Ball::Move(float dt, unsigned int windowWidth)
{
    if(!m_stuck)
    {
        glm::vec2 newPosition = m_position + (m_velocity * dt);
        if(newPosition.x <= 0.f)
        {
            m_velocity.x = -m_velocity.x;
            newPosition.x = 0.f;
        }
        else if(newPosition.x >= windowWidth)
        {
            m_velocity.x = -m_velocity.x;
            newPosition.x = windowWidth;
        }

        if(newPosition.y <= 0.f)
        {
            m_velocity.y = -m_velocity.y;
            newPosition.y = 0.f;
        }

        SetPosition(newPosition);
    }

    return m_position;
}

void Ball::Reset(glm::vec2 pos, glm::vec2 velocity)
{
    SetPosition(pos);
    SetVelocity(velocity);
    SetIsStuck(true);
}

