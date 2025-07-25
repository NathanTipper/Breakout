#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
#include "GameObject.hpp"

class SpriteRenderer;

class GameLevel 
{
public:
    GameLevel() { }
    void Init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
    void Draw(const SpriteRenderer& renderer);
    bool IsComplete();

    std::vector<GameObject> bricks;
    static GameLevel Load(char* file, unsigned int levelWidth, unsigned int levelHeight);
};

#endif
