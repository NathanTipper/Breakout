#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
#include "GameObject.hpp"
class GameLevel 
{
public:
    GameLevel() { }
    GameLevel(char* file, unsigned int levelWidth, unsigned int levelHeight);
    void Init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
    void Load(char* file, unsigned int levelWidth, unsigned int levelHeight);
    bool IsComplete();
private:
    std::vector<GameObject> bricks;
};

#endif
