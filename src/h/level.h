#ifndef CORNERGAME_LEVEL_H
#define CORNERGAME_LEVEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "enums.h"

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
