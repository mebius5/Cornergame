#ifndef CORNERGAME_LEVEL_H
#define CORNERGAME_LEVEL_H

#include <string>

enum Tiles {NONE, TERRAIN, SPAWN, ENEMY, GOAL};

class Level {
    private:
        Tiles** levelContents;
    public:
        int height, width;
        Level(std::string filename);
        ~Level();
        Tiles getTile(int i, int j);
};

#endif
