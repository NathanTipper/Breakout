#ifndef GAME_H
#define GAME_H

#include "Texture2D.h"
#include "GameLevel.hpp"
#include "glm/glm.hpp"
#include "Shader.hpp"
#include "sprite.h"
#include <string>
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

#define MAX_SPRITES 100
class Game
{
public:
    Game();
    Game(unsigned int width, unsigned int height);
    void ProcessInput(float dt);
    void Update(float dt);
    void Render(float dt);

private:
    GameState m_state;
    bool m_keys[1024];
    unsigned int m_width, m_height;

    std::vector<GameLevel> m_levels;
    unsigned int m_currentLevel;
};

void game_initialize(Game* g, unsigned int width, unsigned int height);
void game_process_input(Game* g, float dt);
void game_update(Game* g, float dt);
void game_render(Game* g);
void game_set_sprite_shader(Game* g, ShaderProgram* sprite_shader);
void game_add_sprite(Game* g, std::string texture_path, glm::vec2 position, glm::vec2 scale, glm::vec3 color, float rotation);

#endif
