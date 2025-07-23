#include "GameLevel.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include <fstream>
#include <sstream>
#include <string>

GameLevel::GameLevel(char* file, unsigned int width, unsigned int height)
{
    Load(file, width, height);
}

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
            GameObject obj;
            glm::vec2 position = glm::vec2(unit_width * x, unit_height * y);
            glm::vec2 size = glm::vec2(unit_width, unit_height);
            glm::vec3 color = glm::vec3(1.f);
            Texture2D texture;
            if(tileData[y][x] == 1)
            {
                texture = ResourceManager::GetTexture("block_solid");
                color = glm::vec3(0.8f, 0.8f, 0.7f);
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

            bricks.emplace_back(position, size, texture, color);
        }
    }
}

void GameLevel::Load(char* file, unsigned int levelWidth, unsigned int levelHeight)
{
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
            Init(tileData, levelWidth, levelHeight);
        }
    }
}
