#include "level.h"

Level::Level(int levelNum, int windowW, int windowH):
        windowW(windowW),
        windowH(windowH),
        numHero(0),
        height(0),
        width(0)

{
    std::ifstream csvFS("levels/level"+std::to_string(levelNum)+".csv");
    std::ifstream textFS("levels/level"+std::to_string(levelNum)+".txt");

    if(csvFS.is_open()){
        readCsvFile(csvFS);
        csvFS.close();
    } else if(textFS.is_open()){
        readTxtFile(textFS);
        textFS.close();
    } else {
        std::cerr << "Cannot open level file for level " << levelNum << std::endl;
        return;
    }
}

Level::Level(const char * filename, int windowW, int windowH):
        windowW(windowW),
        windowH(windowH),
        numHero(0)
{
    std::ifstream infile(filename);
    std::string temp(filename);
    if(!infile){
        std::cerr << "Cannot open level file for " << filename << std::endl;
        return;
    }

    if(temp.find(".txt")!=std::string::npos){
        readTxtFile(infile);
    } else if (temp.find(".csv")!=std::string::npos){
        readCsvFile(infile);
    } else{
        std::cerr << "Invalid file extenstion for " << filename << std::endl;
        return;
    }

    infile.close();
}

Level::~Level() {
    delete[] this->levelContents;
    this->stringList.clear();
}

void Level::readTxtFile(std::ifstream & infile) {
    std::string line;

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

    for (int i = 0; i < this->height; i++) {
        std::getline(infile, line);
        if ((int)line.length() < this->width)
            std::cerr << "Error: Level file line " << i+2 << " is too short." << std::endl;
        for (int j = 0; j < this->width; j++) {
            determineTileType(line[j],i,j);
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < windowW/32; j++) {
            Tile type = this->getTile(i, j);
            if (type == TILE_BRICK || type == TILE_GRASS || type == TILE_DIRT || type == TILE_SAND
                || type == TILE_TREE1 || type == TILE_TREE2 || type == TILE_BENCH ||
                type == TILE_BOUNCE) {
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
}

void Level::readCsvFile(std::ifstream &infile) {
    std::string line;
    std::string cell;

    std::getline(infile, line);

    std::stringstream firstLineStream(line);
    //std::cout<<line<<std::endl;
    while(std::getline(firstLineStream,cell,',')){
        if(this->height==0){
            this->height = atoi(cell.c_str());
        } else if (this->width==0){
            this->width = atoi(cell.c_str());
        } else {
            firstLineStream.clear();
        }
    }

    if ((this->height % (windowH/32)) != 0 || (this->width % (windowW/32)) != 0) {
        std::cerr << "Level width needs to be multiple of " << windowW/32
                  << ". Level height needs to be multiple of " << windowH/32
                  << std::endl;
        return;
    }

    // Add enough room for another copy of camera size on the right of the level
    this->contentHeight = height/*+(windowH/32)*/;
    this->contentWidth = width+(windowW/32);
    levelContents = new Tile[this->contentHeight * this->contentWidth];

    // read the file and build the level
    for (int i = 0; i < this->height; i++) {
        std::getline(infile, line);
        //std::cout<<line<<std::endl;
        if ((int)line.length() < this->width)
            std::cerr << "Error: Level file line " << i+2 << " is too short." << std::endl;

        int j=0;
        for(int k = 0; k<(int)line.length();k++){
            if(line[k]!=',' && j <this->width && i <this->height){
                //std::cout<<line[k];
                determineTileType(line[k],i,j);
            } else {
                j++;
            }
        }
        //std::cout<<std::endl;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < windowW/32; j++) {
            Tile type = this->getTile(i, j);
            if (type == TILE_BRICK || type == TILE_GRASS || type == TILE_DIRT || type == TILE_SAND
                || type == TILE_TREE1 || type == TILE_TREE2 || type == TILE_BENCH ||
                type == TILE_BOUNCE) {
                this->getTile(i, j + this->width) = type;
            } else {
                this->getTile(i, j + this->width) = TILE_NONE;
            }
        }
    }

    while (std::getline(infile,line)) {
        std::stringstream lastFewStringStream(line);
        std::getline(lastFewStringStream,cell,',');
        if(cell.length()!=0)
            this->stringList.push_back(cell);
        lastFewStringStream.clear();
    }
}

void Level::determineTileType(char a, int i, int j) {
    Tile tile = TILE_NONE;
    switch (a) {
        case '^': tile = TILE_NONE; break;
        case '#': tile = TILE_BRICK; break;
        case 'W': tile = TILE_GRASS; break;
        case 'D': tile = TILE_DIRT; break;
        case '_': tile = TILE_BOUNCE; break;
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
            std::string errorMsg;
            errorMsg="Unrecognized symbol in level file: ";
            errorMsg+=a;
            errorMsg.append(" at (")
                    .append(std::to_string(i))
                    .append(", ")
                    .append(std::to_string(j))
                    .append(")");
            std::cerr << errorMsg <<std::endl;
    }
    this->getTile(i,j)=tile;
}

Tile& Level::getTile(int i, int j) {
    return this->levelContents[i * this->contentWidth + j];
}

std::vector<std::string>& Level::getStringList() {
    return this->stringList;
}
