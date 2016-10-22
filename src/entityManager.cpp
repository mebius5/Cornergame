#include "entityManager.h"

EntityManager::EntityManager(SDL_Renderer* renderer, std::vector<Command*>& cmdList) :
    commandList(cmdList),
    entityBuilder(renderer),
    numCleanable(0) {
    this->entityBuilder.loadTexture(TEX_HERO, "spritesheets/hero.png");
    this->entityBuilder.loadTexture(TEX_ENEMY, "spritesheets/lax.png");
    this->entityBuilder.loadTexture(TEX_PROJECTILE, "spritesheets/ball.png");
    this->entityBuilder.loadTexture(TEX_BACKGROUND, "resources/jhu-logo.png");
    this->entityBuilder.loadHealthBar(200, 40);
}

EntityManager::~EntityManager() {
    this->entityBuilder.freeTextures();
    this->entityBuilder.freeFonts();
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
        if (StaticCollisionComponent* scc =
                dynamic_cast<StaticCollisionComponent*>(entity->collision)) {
            this->staticCollisionComponents.push_back(scc);
        } else if (DynamicCollisionComponent* dcc =
                dynamic_cast<DynamicCollisionComponent*>(entity->collision)) {
            this->dynamicCollisionComponents.push_back(dcc);
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
    this->cleanupEntities();    // delete all Entities from deletionQueue
    this->entityMap.clear();
    this->aiComponents.clear();
    this->artComponents.clear();
    this->inputComponents.clear();
    this->physicsComponents.clear();
    this->healthComponents.clear();
    this->scoreComponents.clear();
    this->staticCollisionComponents.clear();
    this->dynamicCollisionComponents.clear();
    this->heroEntities.clear();}

/* Entity Creation Methods */
Entity* EntityManager::createHero(TextureEnum texType, int x, int y, SfxEnum sfxType, bool wasd) {
    Entity* entity = this->entityBuilder.createHero(texType, x, y, sfxType, wasd);
    this->addEntity(entity);
    this->heroEntities.push_back(entity);
    return entity;
}

Entity* EntityManager::createEnemy(TextureEnum texType, int x, int y) {
    Entity* entity = this->entityBuilder.createEnemy(texType, x, y, &this->heroEntities);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createBackground(TextureEnum texType, int width, int height) {
    Entity* entity = this->entityBuilder.createBackground(texType, width, height);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createHealthBar(int x, int y, Entity* owner) {
    Entity* entity = this->entityBuilder.createHealthBar(x, y, owner);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createScoreBox(int x, int y, Entity* owner) {
    Entity* entity = this->entityBuilder.createScoreBox(x, y, owner, FONT_GLOBAL, 32);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createCenteredFadeInText(FontEnum font,
                                                const char* text, int fontSize, int r, int g, int b,
                                                int initialAlpha, int windowW, int windowH) {
    Entity* entity = this->entityBuilder.createCenteredFadeInText(
            font, text, fontSize, r, g, b,
            initialAlpha, windowW, windowH);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createHorizontallyCenteredFadeInText(FontEnum font, const char* text,
                                                            int fontSize,
                                                            int r, int g, int b, int initialAlpha,
                                                            int windowW, int yPos,
                                                            int index, int numOptions, StateEnum nextState) {
    Entity* entity = this->entityBuilder.createHorizontallyCenteredFadeInText(
            font, text, fontSize, r, g, b, initialAlpha,
            windowW, yPos, index, numOptions, nextState);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createVictoryZone(int x, int y) {
    Entity* entity = this->entityBuilder.createVictoryZone(x, y);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createTerrain(int x, int y, int numberHorizontal, bool freeTop,
                                     bool freeBot, bool freeRight, bool freeLeft) {
    Entity* entity = this->entityBuilder.createTerrain(
            TT_BRICK, x, y, numberHorizontal, freeTop, freeBot, freeRight, freeLeft);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createProjectile(int x, int y, int dir, int ownerID, ProjEnum /*projType*/) {
    Entity* entity = this->entityBuilder.createProjectile(TEX_PROJECTILE, x, y, dir, ownerID);
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
    for (int i = 0; i < level->contentHeight; i++) {
        for (int j = 0; j < level->contentWidth; j++) {
            switch (level->getTile(i, j)) {
            case TERRAIN: {
                bool freeLeft = (j == 0 || level->getTile(i, j-1) != TERRAIN);
                bool freeRight;     // assigned value later
                bool freeTop = (i == 0 || level->getTile(i-1, j) != TERRAIN);
                bool freeBot = (i == level->contentHeight-1 || level->getTile(i+1, j) != TERRAIN);
                int numberHorizontal = 1;
                int originalJ = j;
                // create horizontal slabs, breaking at each intersection with other terrain rectangles.
                while (j < (level->width-1) && level->getTile(i, j+1) == TERRAIN) {
                    if (i > 0 && level->getTile(i-1, j+1) == TERRAIN && freeTop)
                        break;
                    if (i > 0 && level->getTile(i-1, j+1) != TERRAIN && !freeTop)
                        break;
                    if (i < level->contentHeight-1 && level->getTile(i+1, j+1) == TERRAIN && freeBot)
                        break;
                    if (i < level->contentHeight-1 && level->getTile(i+1, j+1) != TERRAIN && !freeBot)
                        break;
                    numberHorizontal++;
                    j++;
                }
                freeRight = (j == level->contentWidth-1 || level->getTile(i, j+1) != TERRAIN);
                createTerrain(originalJ*32, i*32, numberHorizontal, freeTop, freeBot, freeRight, freeLeft);
                break;
            }
            case ENEMY:
                createEnemy(TEX_ENEMY, j * 32, i * 32);
                break;
            case SPAWN: {
                Entity* hero = createHero(TEX_HERO, j * 32, i * 32, SFX_ALERT, false);
                Entity* hero2 = createHero(TEX_HERO, j * 32, i * 32, SFX_ALERT, true);
                createHealthBar(100, 100, hero);
                createScoreBox(850, 100, hero);
                break;
            }
            case GOAL:
                createVictoryZone(j * 32, i * 32);
                break;
            default:
                break;
            }
        }
    }
}

void EntityManager::printCommands() {
    std::vector<Command*>::iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end(); ++it) {
        if (SwitchStateCommand* ssCmd = dynamic_cast<SwitchStateCommand*>(*it)) {
            std::cout << "Switch Command " << ssCmd->newState << std::endl;
        } else if (PlaySoundCommand* psCmd = dynamic_cast<PlaySoundCommand*>(*it)) {
            std::cout << "Sound Command " << psCmd->sfxType << std::endl;
        } else if (SpawnEntityCommand* seCmd = dynamic_cast<SpawnEntityCommand*>(*it)) {
            std::cout << "Switch Command " << seCmd->projType << std::endl;
        } else if (DespawnEntityCommand* deCmd = dynamic_cast<DespawnEntityCommand*>(*it)) {
            std::cout << "Switch Command " << deCmd->id << std::endl;
        }
    }
}
