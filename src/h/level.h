#ifndef CORNERGAME_LEVEL_H
#define CORNERGAME_LEVEL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "consts.h"

class Level {
private:
    Tile* levelContents;
    std::vector<std::string> stringList;
    int windowW;
    int windowH;
    int numHero;
public:
    int height, width;
    int contentHeight, contentWidth;
    Level(int levelNum, int windowW, int windowH);
    Level(const char * filename, int windowW, int windowH);
    ~Level();
    Tile& getTile(int i, int j);
    void readTxtFile(std::ifstream & infile);
    void readCsvFile(std::ifstream & infile);
    void determineTileType(char a, int i, int j);
    std::vector<std::string>& getStringList();
};

#endif
