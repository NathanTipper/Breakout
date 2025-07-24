#include "Game.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Shader.hpp"
#include "SpriteRenderer/SpriteRenderer.hpp"
#include <string>
#include <iostream>

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

    m_state = GameState::GAME_ACTIVE;
    m_width = width;
    m_height = height;

    ShaderProgram spriteShader = ResourceManager::LoadShader("../shaders/shader.vert", "../shaders/shader.frag", nullptr, "sprite");

    std::cout << "New sprite shader id = " << spriteShader.GetID();

    ResourceManager::LoadTexture("../data/block.png", false, "block");
    ResourceManager::LoadTexture("../data/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("../data/background.jpg", false, "background");
    ResourceManager::LoadTexture("../data/awesomeface.png", false, "face");

    std::string levelsToLoad[] = {
        "one.lvl",
        "two.lvl",
        "three.lvl",
        "four.lvl",
        "five.lvl"
    };


    m_isInitialized = true;
}

void Game::ProcessInput(float dt)
{

}

void Game::Render(float dt)
{
    if(m_renderer)
    {
        for(int i = 0; i < m_levels.size(); ++i)
        {
            GameLevel curr = m_levels[i];
        }
    }
}

void Game::Update(float dt)
{

}
