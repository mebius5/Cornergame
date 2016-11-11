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

    if((this->height%(windowH/32))!=0||(this->width%(windowW/32))!=0){
        std::cerr << "Level width needs to be multiple of " << windowW/32
                  << "Level height needs to be multiple of " << windowH/32
                  << std::endl;
        return;
    }

    // Add enough room for another copy of camera size on the right of the level
    levelContents = new Tiles * [this->height/*+(windowH/32)*/];
    for (int i = 0; i < this->height/*+(windowH/32)*/; i++) {
        levelContents[i] = new Tiles[this->width+(windowW/32)];
    }

    // read the file and build the level
    int numHero = 0;    // number of heroes that have been declared
    Tiles tile = NONE;
    for (int i = 0; i < this->height; i++) {
        std::getline(infile, line);
        for (int j = 0; j < this->width; j++) {
            switch (line.at(j)) {
            case '^': tile = NONE; break;
            case '#': tile = BRICK; break;
            case 'W': tile = GRASS; break;
            case 'D': tile = DIRT; break;
            case '@':
                numHero++;
                if (numHero == 1) {
                    tile = SPAWN1;
                } else if (numHero == 2) {
                    tile = SPAWN2;
                } else {
                    std::cerr << "Error: More than 2 heroes declared in level file." << std::endl;
                }
                break;
            case '-': tile = ENEMY; break;
            case 'O': tile = GOAL; break;
            case 'J': tile = PU_JUMP; break;
            case 'H': tile = PU_HEALTH; break;
            case 'B': tile = PU_BEER; break;
            case 'A': tile = PU_AMMO; break;
            case 'T': tile = TREE1; break;
            case 't': tile = TREE2; break;
            case 'b': tile = BENCH; break;
            case 'F': tile = FADEINTEXT; break;
            case 'N': tile = NORMALTEXT; break;
            default:
                tile = NONE;
                std::cerr << "Unrecognized symbol in level file: " << line.at(j) << std::endl;
            }
            this->levelContents[i][j] = tile;
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < windowW/32; j++) {
            Tiles type = levelContents[i][j];
            if (type==BRICK || type==GRASS || type==DIRT || type==TREE1 || type==TREE2 || type==PU_AMMO
                    || type==PU_BEER || type==PU_JUMP || type==PU_HEALTH || type==BENCH) {
                levelContents[i][j+width]= type;
            } else {
                levelContents[i][j+width]= NONE;
            }
        }
    }

    this->contentHeight = height/*+(windowH/32)*/;
    this->contentWidth = width+(windowW/32);

    while(!infile.eof()){
        std::getline(infile,line);
        this->stringList.push_back(line);
    }

    infile.close();
}

Level::~Level() {       // TODO: verify this is correct
    for (int i = 0; i < this->height/*+(windowH/32)*/; i++)
        delete[] levelContents[i];
    delete[] levelContents;

    this->stringList.clear();
}

Tiles Level::getTile(int i, int j) {
    return this->levelContents[i][j];
}

std::vector<std::string>& Level::getStringList() {
    return this->stringList;
}
