#include "level.h"
#include <iostream>
#include <fstream>
#include <string>

Level::Level(std::string filename) {
    int height, width;
    std::string line;
    std::ifstream infile(filename);
    if (infile.is_open()) {
        // get the size of the level from first line
        getline(infile, line);
        infile >> height;
        infile >> width;

        // initialize level contents
        levelContents = new Tiles * [height];
        for (int i = 0; i < height; i++) {
            levelContents[i] = new Tiles[width];
        }

        // read the file and build the level
        for (int i = 0; i < height; i++) {
            getline(infile, line);
            for (int j = 0; i < width; j++) {
                switch (line[j]) {
                    case '^':
                        levelContents[i][j] = NONE;
                        break;
                    case '#':
                        levelContents[i][j] = TERRAIN;
                        break;
                    default:
                        std::cout << "Unrecognized symbol in level file" << line[j] << std::endl;
                        break;
                }
            }
        }
    } else {
        std::cout << "Could not open level file: " << filename << std::endl;
    }
}

Level::~Level() {
    // TODO
}
