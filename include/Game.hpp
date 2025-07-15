#ifndef GAME_H
#define GAME_H

#include "Texture2D.h"
#include "game_level.hpp"
#include "glm/glm.hpp"
#include "shader.h"
#include "sprite.h"
#include <string>
enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

#define MAX_SPRITES 100
struct Game
{
    GameState state;
    bool keys[1024];
    unsigned int width, height;

    ShaderProgram *sprite_shader;
    Sprite sprites[MAX_SPRITES];
    unsigned int sprite_count;

    std::vector<game_level> levels;
    unsigned int currentLevel;
};

void game_initialize(Game* g, unsigned int width, unsigned int height);
void game_process_input(Game* g, float dt);
void game_update(Game* g, float dt);
void game_render(Game* g);
void game_set_sprite_shader(Game* g, ShaderProgram* sprite_shader);
void game_add_sprite(Game* g, std::string texture_path, glm::vec2 position, glm::vec2 scale, glm::vec3 color, float rotation);

#endif
