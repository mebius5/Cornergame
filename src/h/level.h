#ifndef CORNERGAME_COMMAND_H
#define CORNERGAME_COMMAND_H

#include <string>

enum Tiles {NONE, TERRAIN};

class Level {
    private:
        Tiles** levelContents;
    public:
        Level(std::string filename);
        ~Level();
};

#endif
