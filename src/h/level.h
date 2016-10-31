#ifndef CORNERGAME_LEVEL_H
#define CORNERGAME_LEVEL_H

#include <iostream>
#include <fstream>
#include <string>

enum Tiles {NONE, BRICK, GRASS, SPAWN, ENEMY, GOAL,
    TREE1, TREE2,
    PU_JUMP, PU_HEALTH,};

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
