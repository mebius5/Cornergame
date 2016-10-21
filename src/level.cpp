#include "level.h"
#include <iostream>
#include <fstream>
#include <string>

Level::Level(std::string filename, int windowW, int windowH) {
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

    if((this->height%(windowH/32))!=0||(this->width%(windowW/32))!=0){
        std::cerr<<"Level width needs to be multiples of "<<std::to_string(windowW/32).c_str()
                 <<", and level height needs to be multiples of "<<std::to_string(windowH/32).c_str()
                                                                 <<std::endl;
        return;
    }

    /***
    if(this->width<(windowW/32)*3){
        std::cerr<<"Level width needs to be at least three times bigger than camera width ( at least "
                 <<std::to_string((windowW/32)*3).c_str()<< ")"<<std::endl;
        return ;
    }***/

    // initialize level contents

    // Add enough room for another copy of camera size on the right of the level
    levelContents = new Tiles * [this->height/*+(windowH/32)*/];
    for (int i = 0; i < this->height/*+(windowH/32)*/; i++) {
        levelContents[i] = new Tiles[this->width+(windowW/32)];
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
                    levelContents[i][j] = NONE;
                    std::cout << "Unrecognized symbol in level file: " << line.at(j) << std::endl;
                    break;
            }
        }
    }

    for(int i= 0 ; i<height; i++){
        for (int j = 0; j < windowW/32; j++) {
            if(levelContents[i][j]==TERRAIN){
                levelContents[i][j+width]=levelContents[i][j];
            } else {
                levelContents[i][j+width]= NONE;
            }
        }
    }

    this->contentHeight = height/*+(windowH/32)*/;
    this->contentWidth = width+(windowW/32);

    infile.close();
}

Level::~Level() {
    // TODO
}

Tiles Level::getTile(int i, int j) {
    return this->levelContents[i][j];
}
