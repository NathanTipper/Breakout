#ifndef GAME_H
#define GAME_H

#include "GameObject.hpp"
#include "GameLevel.hpp"
#include "Ball.hpp"
#include "SpriteRenderer/SpriteRenderer.hpp"

#define NUM_KEY_INPUTS 1024
#define INITIAL_BALL_VELOCITY glm::vec2(100.f, -350.f)
#define BALL_RADIUS 12.5f


enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct CollisionResolutionData
{
    bool collided;
    Direction direction;
    glm::vec2 differenceVector;
};

class Game
{
public:
    Game();
    Game(unsigned int width, unsigned int height);
    void Init(unsigned int width, unsigned int height);
    void ProcessInput(float dt);
    void Update(float dt);
    void Render(float dt);

    void SetKey(int index, bool value);
    GameLevel GetCurrentLevel() const;
    void Reset();

private:
    void DetectCollisions();
    CollisionResolutionData AreColliding(const GameObject& o1, const GameObject& o2);
    CollisionResolutionData AreColliding(const Ball& ball, const GameObject& obj);
    Direction GetClosestDirection(const glm::vec2 target);

    GameState m_state;
    SpriteRenderer m_renderer;
    bool m_isInitialized = false;
    bool m_keys[NUM_KEY_INPUTS];
    unsigned int m_width, m_height;
    float m_playerVelocity;
    GameObject m_player;
    Ball m_ball;

    glm::vec2 m_playerStartPos;
    glm::vec2 m_ballStartPos;

    std::vector<GameLevel> m_levels;
    unsigned int m_currentLevel;
};

#endif
