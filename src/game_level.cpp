#include "game_level.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include <fstream>
#include <sstream>
#include <string>

game_level level_load(char *file, unsigned int levelWidth, unsigned int levelHeight)
{
    game_level Result;
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
            level_init(&Result, tileData, levelWidth, levelHeight);
        }
    }

    return Result;
}

void level_init(game_level *level, std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    if(!level)
    {
        return;
    }

    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();

    float unit_width = levelWidth / (float)width;
    float unit_height = levelHeight / (float)height;

    for(unsigned int y = 0; y < height; ++y)
    {
        for(unsigned int x = 0; x < width; ++x)
        {
            GameObject obj;
            obj.position = glm::vec2(unit_width * x, unit_height * y);
            obj.size = glm::vec2(unit_width, unit_height);
            if(tileData[y][x] == 1)
            {
                obj.textureName = "block_solid";
                obj.color = glm::vec3(0.8f, 0.8f, 0.7f);
            }
            else if(tileData[y][x] > 1)
            {
                glm::vec3 color = glm::vec3(1.0f);
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

                obj.textureName = "block";
            }

            level->bricks.push_back(obj);
        }
    }
}
