#ifndef GAME_H
#define GAME_H

#include "GameObject.hpp"
#include "GameLevel.hpp"

class SpriteRenderer;

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
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

private:
    GameState m_state;
    SpriteRenderer* m_renderer;
    bool m_isInitialized = false;
    bool m_keys[1024];
    unsigned int m_width, m_height;

    std::vector<GameLevel> m_levels;
    unsigned int m_currentLevel;
};

#endif
