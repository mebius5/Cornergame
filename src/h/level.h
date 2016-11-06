#ifndef CORNERGAME_LEVEL_H
#define CORNERGAME_LEVEL_H

#include <iostream>
#include <fstream>
#include <string>

enum Tiles {NONE, BRICK, GRASS, SPAWN1, SPAWN2, ENEMY, GOAL,
    PU_JUMP, PU_HEALTH, PU_AMMO,
    PU_BEER,
    TREE1, TREE2, BENCH,
    S1,
};

class Level {
private:
    Tiles** levelContents;
public:
    int height, width;
    int contentHeight, contentWidth;
    Level(std::string filename, int windowW, int windowH);
    ~Level();
    Tiles getTile(int i, int j);
};

#endif
