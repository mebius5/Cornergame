#include "level.h"

Level::Level(std::string filename, int windowW, int windowH) {
    std::string line;
    std::ifstream infile(filename);
    if(!infile.is_open()){
        std::cerr << "Cannot open level file: " << filename << std::endl;
        return;
    }

    // get the size of the level from first line
    infile >> this->height;
    infile >> this->width;
    std::getline(infile, line);

    if ((this->height % (windowH/32)) != 0 || (this->width % (windowW/32)) != 0) {
        std::cerr << "Level width needs to be multiple of " << windowW/32
                  << "Level height needs to be multiple of " << windowH/32
                  << std::endl;
        return;
    }

    // Add enough room for another copy of camera size on the right of the level
    this->contentHeight = height/*+(windowH/32)*/;
    this->contentWidth = width+(windowW/32);
    levelContents = new Tile[this->contentHeight * this->contentWidth];

    // read the file and build the level
    int numHero = 0;    // number of heroes that have been declared
    Tile tile = TILE_NONE;
    for (int i = 0; i < this->height; i++) {
        std::getline(infile, line);
        if ((int)line.length() < this->width)
            std::cerr << "Error: Level file line " << i+2 << " is too short." << std::endl;
        for (int j = 0; j < this->width; j++) {
            switch (line[j]) {
            case '^': tile = TILE_NONE; break;
            case '#': tile = TILE_BRICK; break;
            case 'W': tile = TILE_GRASS; break;
            case 'D': tile = TILE_DIRT; break;
            case 'S': tile = TILE_SAND; break;
            case '@':
                numHero++;
                if (numHero == 1) {
                    tile = TILE_SPAWN1;
                } else if (numHero == 2) {
                    tile = TILE_SPAWN2;
                } else {
                    std::cerr << "Error: More than 2 heroes declared in level file." << std::endl;
                }
                break;
            case '-': tile = TILE_ENEMY; break;
            case 'O': tile = TILE_GOAL; break;
            case 'J': tile = TILE_PU_JUMP; break;
            case 'H': tile = TILE_PU_HEALTH; break;
            case 'B': tile = TILE_PU_BEER; break;
            case 'A': tile = TILE_PU_AMMO; break;
            case 'T': tile = TILE_TREE1; break;
            case 't': tile = TILE_TREE2; break;
            case 'b': tile = TILE_BENCH; break;
            case 'F': tile = TILE_FADEINTEXT; break;
            case 'N': tile = TILE_NORMALTEXT; break;
            default:
                tile = TILE_NONE;
                std::cerr << "Unrecognized symbol in level file: " << line[j] << std::endl;
            }
            this->getTile(i, j) = tile;
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < windowW/32; j++) {
            Tile type = this->getTile(i, j);
            if (type == TILE_BRICK || type == TILE_GRASS || type == TILE_DIRT || type == TILE_SAND
                    || type == TILE_TREE1 || type == TILE_TREE2 || type == TILE_BENCH) {
                this->getTile(i, j + this->width) = type;
            } else {
                this->getTile(i, j + this->width) = TILE_NONE;
            }
        }
    }

    while (!infile.eof()) {
        std::getline(infile, line);
        this->stringList.push_back(line);
    }

    infile.close();
}

Level::~Level() {
    delete[] this->levelContents;
    this->stringList.clear();
}

Tile& Level::getTile(int i, int j) {
    return this->levelContents[i * this->contentWidth + j];
}

std::vector<std::string>& Level::getStringList() {
    return this->stringList;
}
