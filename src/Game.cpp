#include "Game.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Texture2D.h"
#include <string>

void Game::Game()
{ }

void Game::Game(unsigned int width, unsigned int height)
{
    m_state = GameState::GAME_ACTIVE;
    m_width = width;
    m_height = height;

    ResourceManager::LoadTexture("../data/block.png", false, "block");
    ResourceManager::LoadTexture("../data/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("../data/background.jpg", false, "background");
    ResourceManager::LoadTexture("../data/awesomeface.png", false, "face");

    GameLevel lvl1;

}

void game_initialize(Game* g, unsigned int width, unsigned int height)
{
    if(!g)
    {
        return;
    }

    g->state = GameState::GAME_ACTIVE;
    g->width = width;
    g->height = height;
    g->sprite_count = 0;

    sprite_generate_render_data();


    game_add_sprite(g, "background", glm::vec2(0.f, 0.f), glm::vec2(width, height), glm::vec3(1.f), 0.f);
    g->levels.push_back(level_load((char*)("../data/levels/two.lvl"), g->width, g->height / 2));
    g->levels.push_back(level_load((char*)("../data/levels/three.lvl"), g->width, g->height / 2));
    g->levels.push_back(level_load((char*)("../data/levels/four.lvl"), g->width, g->height / 2));
    g->levels.push_back(level_load((char*)("../data/levels/five.lvl"), g->width, g->height / 2));
    g->currentLevel = 0;
}

void game_process_input(Game* g, float dt)
{

}

void game_update(Game* g, float dt)
{

}

void game_render(Game* g)
{
    sprite_draw(g->sprites, g->sprite_count, g->sprite_shader);
}

void game_set_sprite_shader(Game *g, ShaderProgram *sprite_shader)
{
    g->sprite_shader = sprite_shader;
}

void game_add_sprite(Game* g, std::string texture_name, glm::vec2 position, glm::vec2 scale, glm::vec3 color, float rotation)
{
    if(g->sprite_count >= MAX_SPRITES)
    {
        return;
    }

    g->sprites[g->sprite_count].texture = ResourceManager::GetTexture(texture_name);
    g->sprites[g->sprite_count].position = position;
    g->sprites[g->sprite_count].size = scale;
    g->sprites[g->sprite_count].color = color;
    g->sprites[g->sprite_count].rotation = rotation;

    g->sprite_count++;
}
