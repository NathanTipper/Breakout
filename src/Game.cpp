#include "Game.hpp"
#include "GameObject.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Shader.hpp"
#include "SpriteRenderer/SpriteRenderer.hpp"
#include <string>
#include <iostream>
#include "glfw3.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Game::Game()
{ }

Game::Game(unsigned int width, unsigned int height)
{
    Init(width, height);
}

void Game::Init(unsigned int width, unsigned int height)
{
    if(m_isInitialized)
    {
        return;
    }

    // Load Textures
    ResourceManager::LoadTexture("../data/block.png", false, "block");
    ResourceManager::LoadTexture("../data/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("../data/background.jpg", false, "background");
    ResourceManager::LoadTexture("../data/paddle.png", false, "paddle");
    ResourceManager::LoadTexture("../data/awesomeface.png", true, "face");

    // Initialize member variables
    m_state = GameState::GAME_ACTIVE;
    m_width = width;
    m_height = height;
    m_playerVelocity = 500.f;

    glm::vec2 playerSize = glm::vec2(100.f, 20.f);
    m_playerStartPos = glm::vec2(m_width * 0.5f - playerSize.x * 0.5f, m_height - playerSize.y);

    m_player.SetPosition(m_playerStartPos);
    m_player.SetSize(playerSize);
    m_player.SetTexture(ResourceManager::GetTexture("paddle"));

    m_ballStartPos = m_playerStartPos+ glm::vec2((playerSize.x * 0.5f) - BALL_RADIUS, -BALL_RADIUS * 2.f);
    m_ball.SetPosition(m_ballStartPos);
    m_ball.SetTexture(ResourceManager::GetTexture("face"));
    m_ball.SetVelocity(INITIAL_BALL_VELOCITY);
    m_renderer.Init();

    ShaderProgram spriteShader = ResourceManager::LoadShader("../shaders/shader.vert", "../shaders/shader.frag", nullptr, "sprite");
    // Initialize shaders
    spriteShader.Use();
    spriteShader.SetInt("image", 0);
    glm::mat4 projection = glm::ortho(0.f, 800.f, 600.f, 0.f, -1.f, 1.f);
    spriteShader.SetMatrix("projection", glm::value_ptr(projection));

    m_renderer.SetShader("sprite");

    // Load Levels
    char* levelsToLoad[] = {
        (char*)"../data/levels/one.lvl",
        (char*)"../data/levels/two.lvl",
        (char*)"../data/levels/three.lvl",
        (char*)"../data/levels/four.lvl",
    };

    for(char* level: levelsToLoad)
    {
        // TODO: Is this bad? I think I am creating two GameLevels on each iteration... Avoidable? Move semantics perhaps?
        m_levels.push_back(GameLevel::Load(level, m_width, m_height * 0.5f));
    }
    m_currentLevel = 0;

    m_isInitialized = true;
}

void Game::ProcessInput(float dt)
{
    if(m_state == GAME_ACTIVE)
    {
        float velocity = m_playerVelocity * dt;
        if(m_keys[GLFW_KEY_A])
        {
            glm::vec2 newPlayerPos = m_player.GetPosition();
            if(newPlayerPos.x > 0.f)
            {
                newPlayerPos.x -= velocity; 
            }
            m_player.SetPosition(newPlayerPos);

            if(m_ball.IsStuck())
            {
                glm::vec2 ballPos = m_ball.GetPosition();
                m_ball.SetPosition(glm::vec2(ballPos.x - velocity, ballPos.y));
            }
        }

        if(m_keys[GLFW_KEY_D])
        {
            glm::vec2 newPlayerPos = m_player.GetPosition();
            if(newPlayerPos.x < m_width - m_player.GetSize().x)
            {
                newPlayerPos.x += velocity;
            }
            m_player.SetPosition(newPlayerPos);

            if(m_ball.IsStuck())
            {
                glm::vec2 ballPos = m_ball.GetPosition();
                m_ball.SetPosition(glm::vec2(ballPos.x + velocity, ballPos.y));
            }
        }

        if(m_keys[GLFW_KEY_SPACE])
        {
            m_ball.SetIsStuck(false);
        }
    }
}

void Game::Render(float dt)
{
    m_renderer.DrawSprite(ResourceManager::GetTexture("background"), 
                            glm::vec2(0.f, 0.f), glm::vec2(m_width, m_height));
    m_levels[m_currentLevel].Draw(m_renderer);
    m_renderer.DrawSprite(m_player);
    m_renderer.DrawSprite(static_cast<GameObject>(m_ball));
}

void Game::Update(float dt)
{
    m_ball.Move(dt, m_width);
    if(m_ball.GetPosition().y >= m_height)
    {
        Reset();
    }
    DetectCollisions();
}

void Game::SetKey(int index, bool value)
{
    if(index >= 0 && index < NUM_KEY_INPUTS)
    {
        m_keys[index] = value;
    }
}

GameLevel Game::GetCurrentLevel() const
{
    if(m_currentLevel >= 0 && m_currentLevel < m_levels.size())
    {
        return m_levels[m_currentLevel];
    }

    return GameLevel();
}

void Game::DetectCollisions()
{
    if(m_ball.IsStuck())
    {
        return;
    }

    for(GameObject& brick : m_levels[m_currentLevel].bricks)
    {
        if(!brick.IsDestroyed())
        {
            CollisionResolutionData crd = AreColliding(m_ball, brick);
            if(crd.collided)
            {
                glm::vec2 currBallVelocity = m_ball.GetVelocity();
                glm::vec2 currBallPosition = m_ball.GetPosition();
                if(!brick.IsSolid())
                {
                    brick.SetIsDestroyed(true);
                }

                if(crd.direction == LEFT || crd.direction == RIGHT)
                {
                    m_ball.SetVelocity(glm::vec2(-currBallVelocity.x, currBallVelocity.y));
                    float overlap = m_ball.GetRadius() - std::abs(crd.differenceVector.x);
                    if(crd.direction == LEFT)
                    {
                        m_ball.SetPosition(glm::vec2(currBallPosition.x + overlap, currBallPosition.y));
                    }
                    else
                    {
                        m_ball.SetPosition(glm::vec2(currBallPosition.x - overlap, currBallPosition.y));
                    }
                }
                else
                {
                    m_ball.SetVelocity(glm::vec2(currBallVelocity.x, -currBallVelocity.y));
                    float overlap = m_ball.GetRadius() - std::abs(crd.differenceVector.y);
                    if(crd.direction == DOWN)
                    {
                        m_ball.SetPosition(glm::vec2(currBallPosition.x, currBallPosition.y + overlap));
                    }
                    else
                    {
                        m_ball.SetPosition(glm::vec2(currBallPosition.x, currBallPosition.y - overlap));
                    }
                }

                return;
            }
        }
    }

    CollisionResolutionData crd = AreColliding(m_ball, m_player);
    if(crd.collided)
    {
        float playerCenter = m_player.GetPosition().x + m_player.GetSize().x * 0.5f;
        float distance = (m_ball.GetPosition().x + m_ball.GetRadius()) - playerCenter;
        float percentage = distance / (m_player.GetSize().x * 0.5f);
        float strength = 2.0f;

        glm::vec2 oldVelocity = m_ball.GetVelocity();
        glm::vec2 newVelocity = glm::vec2(INITIAL_BALL_VELOCITY.x * percentage * strength, oldVelocity.y);
        newVelocity.y = -1.0f * abs(newVelocity.y);
        newVelocity = glm::normalize(newVelocity) * glm::length(oldVelocity);

        m_ball.SetVelocity(newVelocity);
    }
}

CollisionResolutionData Game::AreColliding(const Ball& ball, const GameObject& obj)
{
    CollisionResolutionData Result;

    glm::vec2 circleCenter = ball.GetPosition() + ball.GetRadius();

    glm::vec2 objSize = obj.GetSize();
    glm::vec2 objPos = obj.GetPosition();

    glm::vec2 halfExtents = objSize * 0.5f;
    glm::vec2 objCenter = objPos + halfExtents;

    glm::vec2 diff = circleCenter - objCenter;
    glm::vec2 clamped_diff = glm::clamp(diff, -halfExtents, halfExtents);
    glm::vec2 closest = objCenter + clamped_diff;

    diff = closest - circleCenter;

    Result.collided = glm::length(diff) < ball.GetRadius();
    if(Result.collided)
    {
        Result.direction = GetClosestDirection(diff);
        Result.differenceVector = diff;
    }
    else
    {
        Result.direction = UP;
        Result.differenceVector = glm::vec2(0.f);
    }

    return Result;
}

CollisionResolutionData Game::AreColliding(const GameObject& o1, const GameObject& o2)
{
    CollisionResolutionData Result;
    bool x_collision = o1.GetPosition().x + o1.GetSize().x >= o2.GetPosition().x &&
                        o2.GetPosition().x + o2.GetSize().x >= o1.GetPosition().x;
    bool y_collision = o1.GetPosition().y + o1.GetSize().y >= o2.GetPosition().y &&
                        o2.GetPosition().y + o2.GetSize().y >= o1.GetPosition().y;

    Result.collided = x_collision && y_collision;

    return Result;
}

Direction Game::GetClosestDirection(const glm::vec2 target)
{
    glm::vec2 compass[] = {
        { 0.f, -1.f },
        { -1.f, 0.f },
        { 1.f, 0.f }
    };

    glm::vec2 normalized_target = glm::normalize(target);
    Direction Result = UP;
    float max = glm::dot(normalized_target, { 0.f, 1.f });
    for(int i = 0; i < 3; ++i)
    {
        float dot = glm::dot(normalized_target, compass[i]);
        if(dot > max)
        {
            max = dot;
            Result = (Direction)(i + 1);
        }
    }

    return Result;
}

void Game::Reset()
{
    for(GameObject& brick : m_levels[m_currentLevel].bricks)
    {
        brick.SetIsDestroyed(false);
    }

    m_player.SetPosition(m_playerStartPos);
    m_ball.Reset(m_ballStartPos, INITIAL_BALL_VELOCITY);
}
