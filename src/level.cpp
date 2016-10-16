#include "level.h"
#include <iostream>
#include <fstream>
#include <string>

Level::Level(std::string filename) {
    std::string line;
    std::ifstream infile(filename);
    if(!infile.is_open()){
        std::cerr<<"Cannot open level file: "+filename<<std::endl;
        return ;
    }

    // get the size of the level from first line
    infile >> this->height;
    infile >> this->width;
    getline(infile, line);

    // initialize level contents
    levelContents = new Tiles * [this->height];
    for (int i = 0; i < this->height; i++) {
        levelContents[i] = new Tiles[this->width];
    }

    // read the file and build the level
    for (int i = 0; i < this->height; i++) {
        getline(infile, line);
        for (int j = 0; j < this->width; j++) {
            switch (line.at(j)) {
                case '^':
                    levelContents[i][j] = NONE;
                    break;
                case '#':
                    levelContents[i][j] = TERRAIN;
                    break;
                case '@':
                    levelContents[i][j] = SPAWN;
                    break;
                case '-':
                    levelContents[i][j] = ENEMY;
                    break;
                case 'O':
                    levelContents[i][j] = GOAL;
                    break;
                default:
                    std::cout << "Unrecognized symbol in level file " << line.at(j) << std::endl;
                    break;
            }
        }
    }

    infile.close();
}

Level::~Level() {
    // TODO
}

Tiles Level::getTile(int i, int j) {
    return this->levelContents[i][j];
}
