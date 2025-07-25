#include "GameLevel.hpp"
#include "GameObject.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "SpriteRenderer/SpriteRenderer.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

void GameLevel::Init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();

    float unit_width = levelWidth / (float)width;
    float unit_height = levelHeight / (float)height;

    for(unsigned int y = 0; y < height; ++y)
    {
        for(unsigned int x = 0; x < width; ++x)
        {
            GameObject brick;
            brick.SetPosition(glm::vec2(unit_width * x, unit_height * y));
            brick.SetSize(glm::vec2(unit_width, unit_height));
            brick.SetIsDestroyed(false);
            glm::vec3 color = glm::vec3(1.f);
            Texture2D texture;
            if(tileData[y][x] == 1)
            {
                texture = ResourceManager::GetTexture("block_solid");
                color = glm::vec3(0.8f, 0.8f, 0.7f);
                brick.SetIsSolid(true);
            }
            else if(tileData[y][x] > 1)
            {
                color = glm::vec3(1.0f);
                if(tileData[y][x] == 2)
                {
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                }
                else if(tileData[y][x] == 3)
                {
                    color = glm::vec3(0.f, 0.7f, 0.f);
                }
                else if(tileData[y][x] == 4)
                {
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                }
                else if(tileData[y][x] == 5)
                {
                    color = glm::vec3(1.f, 0.5f, 0.f);
                }

                texture = ResourceManager::GetTexture("block");
            }

            brick.SetColor(color);
            brick.SetTexture(texture);

            bricks.push_back(brick);
        }
    }
}

GameLevel GameLevel::Load(char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    GameLevel Result;
    unsigned int tileCode;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;
    if(fstream)
    {
        while(std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while(sstream >> tileCode)
            {
                row.push_back(tileCode);
            }

            tileData.push_back(row);
        }

        if(tileData.size() > 0)
        {
            Result.Init(tileData, levelWidth, levelHeight);
        }
    }

    return Result;
}

void GameLevel::Draw(const SpriteRenderer& renderer)
{
    for(GameObject& brick : bricks)
    {
        if(!brick.IsDestroyed())
        {
            brick.Draw(renderer);
        }
    }
}
