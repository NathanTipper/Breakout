#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
#include "game_object.hpp"
struct game_level
{
    std::vector<GameObject> bricks;
};

void level_init(game_level* level, std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
game_level level_load(char* file, unsigned int levelWidth, unsigned int levelHeight);
void level_is_complete(game_level* level);
#endif
