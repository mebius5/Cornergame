#ifndef CORNERGAME_LEVEL_H
#define CORNERGAME_LEVEL_H

#include <string>

enum Tiles {NONE, TERRAIN};

class Level {
    private:
        Tiles** levelContents;
    public:
        int height, width;
        Level(std::string filename);
        ~Level();
};

#endif
