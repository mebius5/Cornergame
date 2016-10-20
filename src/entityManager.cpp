#include "entityManager.h"

/* Constructor and Destructor */
EntityManager::EntityManager(SDL_Renderer* renderer, std::vector<Command*>& cmdList) :
        commandList(cmdList),
        entityBuilder(renderer),
        numCleanable(0) {
}

EntityManager::~EntityManager() {
    this->clear();
}

/* Entity Insertion and Deletion */
void EntityManager::addEntity(Entity* entity) {
    int id = entity->getId();
    this->entityMap[id] = entity;

    if (entity->ai) {
        this->aiComponents.push_back(entity->ai);
    }
    if (entity->art) {
        this->artComponents.push_back(entity->art);
    }
    if (entity->collision) {
        if (entity->collision->staticObject) {
            this->staticCollisionComponents.push_back(entity->collision);
        } else {
            this->volatileCollisionComponents.push_back(entity->collision);
        }
    }
    if (entity->input) {
        this->inputComponents.push_back(entity->input);
    }
    if (entity->physics) {
        this->physicsComponents.push_back(entity->physics);
    }
    if (entity->health) {
        this->healthComponents.push_back(entity->health);
    }
    if (entity->score) {
        this->scoreComponents.push_back(entity->score);
    }
}

void EntityManager::deleteEntity(int id) {
    if (this->entityMap.count(id) == 0) {
        return;
    }
    Entity* entity = this->entityMap[id];
    this->deletionQueue.push(entity);
    this->entityMap.erase(id);

    if (entity->ai)
        entity->ai->invalidate();
    if (entity->art)
        entity->art->invalidate();
    if (entity->collision)
        entity->collision->invalidate();
    if (entity->input)
        entity->input->invalidate();
    if (entity->physics)
        entity->physics->invalidate();
    if (entity->health)
        entity->health->invalidate();
    if (entity->score)
        entity->score->invalidate();
}

void EntityManager::cleanupEntities() {
    for (int i = 0; i < this->numCleanable; i++) {
        Entity* entity = this->deletionQueue.front();
        this->deletionQueue.pop();
        delete entity;
    }

    this->numCleanable = this->deletionQueue.size();
}

void EntityManager::clear() {
    std::unordered_map<int, Entity*>::const_iterator it;
    for (it = this->entityMap.begin(); it != this->entityMap.end(); ++it)
        delete it->second;      // delete all Entities from map
    this->entityMap.clear();
    this->aiComponents.clear();
    this->artComponents.clear();
    this->inputComponents.clear();
    this->physicsComponents.clear();
    this->healthComponents.clear();
    this->scoreComponents.clear();
    this->staticCollisionComponents.clear();
    this->heroEntities.clear();
    this->volatileCollisionComponents.clear();
}

/* Entity Creation Methods */
Entity* EntityManager::createHero(int x, int y, SfxEnum sfxType, bool wasd) {
    Entity* entity = this->entityBuilder.createHero(x, y, sfxType, wasd);
    this->addEntity(entity);

    this->heroEntities.push_back(entity);


    return entity;
}

Entity* EntityManager::createEnemy(int x, int y) {
    Entity* entity = this->entityBuilder.createEnemy(x, y, &this->heroEntities);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createBackground(const char* filename, int w, int h) {
    Entity* entity = this->entityBuilder.createBackground(filename, w, h);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createHealthBar(int x, int y, int width, int height, Entity* owner) {
    Entity* entity = this->entityBuilder.createHealthBar(x, y, width, height, owner);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createScoreBox(int x, int y, Entity* owner) {
    Entity* entity = this->entityBuilder.createScoreBox(x, y, owner);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createCenteredFadeInText(const char* fontName,
                                                const char* text, int fontSize, int r, int g, int b,
                                                int initialAlpha, int windowW, int windowH) {

    Entity* entity = this->entityBuilder.createCenteredFadeInText(fontName,
                                                                  text, fontSize, r, g, b,
                                                                  initialAlpha, windowW, windowH);
    this->addEntity(entity);
    return entity;
}

Entity * EntityManager::createHorizontallyCenteredFadeInText(const char* fontName,
                                                             const char* text,
                                                             int fontSize,
                                                             int r, int g, int b, int initialAlpha,
                                                             int windowW, int yPos,
                                                             int index, int numOptions, StateEnum nextState) {
    Entity* entity = this->entityBuilder.createHorizontallyCenteredFadeInText(
            fontName, text, fontSize, r, g, b, initialAlpha,
            windowW, yPos, index, numOptions, nextState);
    this->addEntity(entity);
    return entity;
}

Entity * EntityManager::createVictoryZone(int x, int y) {
    Entity* entity = this->entityBuilder.createVictoryZone(x, y);
    this->addEntity(entity);
    return entity;
}

Entity * EntityManager::createTerrain(int x, int y, int numberHorizontal, bool freeTop, bool freeBot,
                                      bool freeRight, bool freeLeft) {
    Entity * entity = this->entityBuilder.createTerrain(x, y, numberHorizontal, freeTop, freeBot, freeRight, freeLeft);
    this->addEntity(entity);
    return entity;
}

Entity * EntityManager::createProjectile(int x, int y, int dir, int ownerID, ProjEnum /*projType*/) {
    Entity * entity = this->entityBuilder.createProjectile(x, y, dir, ownerID);
    this->addEntity(entity);
    return entity;
}

void EntityManager::handleSpawns() {
    std::vector<Command*>::iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end(); ) {
        if (SpawnEntityCommand* eCmd = dynamic_cast<SpawnEntityCommand*>(*it)) {
            this->createProjectile(eCmd->x, eCmd->y, eCmd->dir, eCmd->ownerID, eCmd->projType);
            *it = this->commandList.back();
            this->commandList.pop_back();
        } else if (DespawnEntityCommand* dCmd = dynamic_cast<DespawnEntityCommand*>(*it)) {
            this->deleteEntity(dCmd->id);
            *it = this->commandList.back();
            this->commandList.pop_back();
        } else {
            ++it;
        }
    }
}

void EntityManager::populateLevel(Level* level) {
    Entity* hero;
    Entity* hero2;
    bool freeRight;
    bool freeLeft;
    bool freeTop;
    bool freeBot;

    for (int i = 0; i < level->contentHeight; i++) {
        for (int j = 0; j < level->contentWidth; j++) {
            switch(level->getTile(i, j)) {
                case TERRAIN:
                {
                    freeRight = true;
                    freeLeft = true;
                    int numberHorizontal=1;
                    int originalJ= j;
                    if (j>0 && level->getTile(i,j-1) == TERRAIN) {
                        freeLeft = false;
                    }
                    while(true){
                        if( j < (level->width -1) && level->getTile(i,j+1) == TERRAIN){
                            numberHorizontal++;
                            j++;
                        } else{
                            break;
                        }
                    }
                    if (j < (level->width-1) && level->getTile(i,j+1) == TERRAIN) {
                        freeRight = false;
                    }
                    freeBot = false;
                    freeTop = false;
                    for(int k = originalJ; k < originalJ+numberHorizontal;k++){
                        if (i>0 && level->getTile(i-1,k) != TERRAIN) {
                            freeTop = true;
                        }
                        if (i < (level->height -1) && level->getTile(i+1,k) != TERRAIN) {
                            freeBot = true;
                        }
                    }
                    createTerrain(originalJ * 32, i * 32, numberHorizontal, freeTop, freeBot, freeRight, freeLeft);
                    break;
                }
                case ENEMY:
                    createEnemy(j * 32, i * 32);
                    break;
                case SPAWN:
                    hero = createHero(j * 32, i * 32, SFX_ALERT, false);
                    hero2 = createHero(j * 32, i * 32, SFX_ALERT, true);
                    createHealthBar(100, 100, 200, 40, hero);
                    createScoreBox(850, 100, hero);
                    break;
                case GOAL:
                    createVictoryZone(j * 32, i * 32);
                    break;
                default:
                    break;
            }
        }
    }
}
