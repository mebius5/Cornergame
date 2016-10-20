#ifndef CORNERGAME_LEVEL_H
#define CORNERGAME_LEVEL_H

#include <string>

enum Tiles {NONE, TERRAIN, SPAWN, ENEMY, GOAL};

class Level {
private:
    Tiles** levelContents;
    int windowW;
    int windowH;
public:
    int height, width;
    int contentHeight, contentWidth;
    Level(std::string filename, int windowW, int windowH);
    ~Level();
    Tiles getTile(int i, int j);
};

#endif
