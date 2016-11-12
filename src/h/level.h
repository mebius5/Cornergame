#ifndef CORNERGAME_LEVEL_H
#define CORNERGAME_LEVEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum Tile {NONE, BRICK, GRASS, DIRT, SPAWN1, SPAWN2, ENEMY, GOAL,
    PU_JUMP, PU_HEALTH, PU_AMMO, PU_BEER,
    TREE1, TREE2, BENCH, FADEINTEXT, NORMALTEXT
};

class Level {
private:
    Tile* levelContents;
    std::vector<std::string> stringList;
public:
    int height, width;
    int contentHeight, contentWidth;
    Level(std::string filename, int windowW, int windowH);
    ~Level();
    Tile& getTile(int i, int j);
    std::vector<std::string>& getStringList();
};

#endif
