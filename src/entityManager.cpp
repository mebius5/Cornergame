#include "entityManager.h"
#include <math.h>
#include <iostream>

EntityManager::EntityManager(SDL_Renderer *renderer, std::vector<Command *> &cmdList, int windowW) :
    commandList(cmdList),
    entityBuilder(renderer),
    windowW(windowW),
    numCleanable(0) {
    this->entityBuilder.loadTexture(TEX_HERO, "spritesheets/hero.png");
    this->entityBuilder.loadTexture(TEX_HERO2, "spritesheets/hero2.png");
    this->entityBuilder.loadTexture(TEX_ENEMY, "spritesheets/lax.png");
    this->entityBuilder.loadTexture(TEX_PROJECTILE, "spritesheets/ball.png");
    this->entityBuilder.loadTexture(TEX_BACKGROUND, "resources/jhu-logo.png");
    this->entityBuilder.loadTexture(TEX_PWRUP_INFHEALTH, "resources/star.png");
    this->entityBuilder.loadTexture(TEX_PWRUP_INFJUMP, "resources/wings.png");
    this->entityBuilder.loadTexture(TEX_PWRUP_AMMO, "resources/paper.png");
    this->entityBuilder.loadTexture(TEX_PWRUP_BEER, "resources/beer.png");
    this->entityBuilder.loadTexture(TEX_TREE1, "resources/greentree1.png");
    this->entityBuilder.loadTexture(TEX_TREE2, "resources/greentree2.png");
    this->entityBuilder.loadTexture(TEX_BENCH, "resources/bench.png");
    this->entityBuilder.loadHealthBar(200, 40);
    this->entityBuilder.loadAmmoBar(200, 40);
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

            if(PowerUpCollisionComponent * puc = dynamic_cast<PowerUpCollisionComponent*>(entity->collision)){
                this->powerUpCollisionComponents.push_back(puc);
            }
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
    if (entity->powerUp){
        this->powerUpComponents.push_back(entity->powerUp);
    }
}

void EntityManager::initRespawns() {
    std::unordered_map<int, Entity*>::const_iterator it;
    for (it = this->entityMap.begin(); it != this->entityMap.end(); ++it)
        if (dynamic_cast<EnemyCollisionComponent*>(it->second->collision))
            this->respawnEntities.push_back(it->second);
}

void EntityManager::deleteEntity(int id) {
    Entity* entity = this->hideEntity(id);
    if (entity)
        this->deletionQueue.push(entity);
}

Entity* EntityManager::hideEntity(int id) {
    if (this->entityMap.count(id) == 0) {
        return NULL;
    }
    Entity* entity = this->entityMap[id];
    this->entityMap.erase(id);
    entity->invalidate();
    return entity;
}

void EntityManager::cleanupEntities() {
    std::vector<HealthComponent*>::iterator it;
    for (it = this->healthComponents.begin(); it != this->healthComponents.end();) {
        if (!(*it)->isValid()) {        // remove invalid components
            *it = this->healthComponents.back();
            this->healthComponents.pop_back();
        } else
            ++it;
    }

    for (int i = 0; i < this->numCleanable; i++) {
        Entity* entity = this->deletionQueue.front();
        this->deletionQueue.pop();
        delete entity;
    }

    this->numCleanable = this->deletionQueue.size();
}

void EntityManager::clear() {
    this->cleanupEntities();    // delete all Entities from deletionQueue
    std::vector<Entity*>::const_iterator ents;
    for (ents = this->respawnEntities.begin(); ents != this->respawnEntities.end(); ++ents) {
        if (this->entityMap.count((*ents)->getId()) == 0)
            delete *ents;
    }

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
    this->dynamicCollisionComponents.clear();
    this->powerUpComponents.clear();
    this->powerUpCollisionComponents.clear();
    this->heroEntities.clear();
    this->respawnEntities.clear();
}

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

Entity* EntityManager::createAmmoBar(int x, int y, Entity* owner) {
    Entity* entity = this->entityBuilder.createAmmoBar(x, y, owner);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createScoreBox(int x, int y, Entity* owner) {
    Entity* entity = this->entityBuilder.createScoreBox(x, y, owner, FONT_GLOBAL, 32);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createFadeInText(FontEnum font,
                                                const char* text, int fontSize, int r, int g, int b,
                                                int initialAlpha, int windowW, int x, int y) {
    Entity* entity = this->entityBuilder.createFadeInText(
            font, text, fontSize, r, g, b,
            initialAlpha, windowW, x, y);
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

Entity* EntityManager::createHorizontallyCenteredFadeInText(FontEnum font, const char *text, int fontSize, int r, int g,
                                                            int b, int initialAlpha, int windowW, int yPos) {
    Entity * entity = this->entityBuilder.createHorizontallyCenteredFadeInText(
            font, text, fontSize, r, g, b, initialAlpha,
            windowW, yPos
    );
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createHorizontallyCenteredFadeInMenuText(FontEnum font, const char *text,
                                                                int fontSize,
                                                                int r, int g, int b, int initialAlpha,
                                                                int windowW, int yPos,
                                                                int index, int numOptions, StateEnum nextState) {
    Entity* entity = this->entityBuilder.createHorizontallyCenteredFadeInMenuText(
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

Entity* EntityManager::createPowerUp(TextureEnum pwrUpType, int x, int y) {
    Entity * entity = this->entityBuilder.createPowerUp(pwrUpType, x, y);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createStaticBackgroundObject(TextureEnum texType, int x, int y) {
    Entity* entity = this->entityBuilder.createStaticBackgroundObject(texType, x,y);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createTerrain(Tiles tileType, int x, int y, int numberHorizontal, bool freeTop,
                                     bool freeBot, bool freeRight, bool freeLeft) {
    TerrainTexEnum texType = (tileType == BRICK ? TT_BRICK : TT_GRASS);
    Entity* entity = this->entityBuilder.createTerrain(
            texType, x, y, numberHorizontal, freeTop, freeBot, freeRight, freeLeft);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createProjectile(int x, int y, float charge, int dir, int ownerID, ProjEnum /*projType*/) {
    // Home in on the nearest thing that takes damage
    float min_dist = -1;
    float sqnorm = 0;
    Entity* closest_entity = NULL;
    std::vector<HealthComponent*>::iterator it;
    for (it = this->healthComponents.begin(); it != this->healthComponents.end();) {
        Entity* hpEntity = (*it)->entity;
        if ((hpEntity->x - x) * dir > 0 && ownerID != hpEntity->getId()) { // only if in the right direction and not me
            sqnorm = pow(hpEntity->x - x, 2) + pow(hpEntity->y - y, 2);
            if (min_dist == -1 || sqnorm < min_dist) {
                min_dist = sqnorm;
                closest_entity = hpEntity;
            }
        }
        ++it;
    }
    Entity* entity = this->entityBuilder.createProjectile(TEX_PROJECTILE, x, y, charge, dir, ownerID, closest_entity);
    this->addEntity(entity);
    return entity;
}

void EntityManager::handleSpawns() {
    std::vector<Command*>::iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end(); ) {
        if (SpawnProjCommand* eCmd = dynamic_cast<SpawnProjCommand*>(*it)) {
            this->createProjectile(eCmd->x, eCmd->y, eCmd->charge, eCmd->dir, eCmd->ownerID, eCmd->projType);
        } else if (DespawnEntityCommand* dCmd = dynamic_cast<DespawnEntityCommand*>(*it)) {
            this->deleteEntity(dCmd->id);
        } else if (TempHideCommand* tCmd = dynamic_cast<TempHideCommand*>(*it)) {
            this->hideEntity(tCmd->id);
        } else if (dynamic_cast<LoopLevelCommand*>(*it)){
            std::vector<PowerUpCollisionComponent*>::iterator pu;
            for(pu = this->powerUpCollisionComponents.begin(); pu != this->powerUpCollisionComponents.end(); ++pu){
                (*pu)->setIsClaimed(false);
                (*pu)->entity->art->isVisible=true;
            }
            std::vector<Entity*>::iterator ents;
            for (ents = this->respawnEntities.begin(); ents != this->respawnEntities.end(); ++ents) {
                Entity* entity = *ents;
                if (this->entityMap.count(entity->getId()) == 0) {
                    entity->validate();
                    this->addEntity(entity);
                    entity->x = entity->initialX;
                    entity->y = entity->initialY;
                } else if (entity->x < this->windowW)
                    entity->x = this->windowW + (rand() % 100);
            }
        } else {
            ++it;
            continue;
        }

        *it = this->commandList.back();
        this->commandList.pop_back();
    }
}

void EntityManager::populateLevel(Level* level) {
    int stringCount=0;

    for (int i = 0; i < level->contentHeight; i++) {
        for (int j = 0; j < level->contentWidth; j++) {
            switch (level->getTile(i, j)) {
            case BRICK:
            case GRASS: {
                bool freeLeft = (j == 0 || (level->getTile(i, j-1) != BRICK && level->getTile(i, j-1) != GRASS));
                bool freeRight;     // assigned value later
                bool freeTop = (i == 0 || (level->getTile(i-1, j) != BRICK && level->getTile(i-1, j) != GRASS));
                bool freeBot = (i == level->contentHeight-1 || (level->getTile(i+1, j) != BRICK && level->getTile(i+1, j) != GRASS));
                int numberHorizontal = 1;
                int originalJ = j;
                // create horizontal slabs, breaking at each intersection with other terrain rectangles.
                while (j < (level->width-1) && (level->getTile(i, j+1) == BRICK || level->getTile(i, j+1) == GRASS)) {
                    if (i > 0 && freeTop && (level->getTile(i-1, j+1) == BRICK || level->getTile(i-1, j+1) == GRASS))
                        break;
                    if (i > 0 && !freeTop && (level->getTile(i-1, j+1) != BRICK && level->getTile(i-1, j+1) != GRASS))
                        break;
                    if (i < level->contentHeight-1 && freeBot && (level->getTile(i+1, j+1) == BRICK || level->getTile(i+1, j+1) == GRASS))
                        break;
                    if (i < level->contentHeight-1 && !freeBot && (level->getTile(i+1, j+1) != BRICK && level->getTile(i+1, j+1) != GRASS))
                        break;
                    numberHorizontal++;
                    j++;
                }
                freeRight = (j == level->contentWidth-1 || (level->getTile(i, j+1) != BRICK && level->getTile(i, j+1) != GRASS));
                createTerrain(level->getTile(i, j), originalJ*32, i*32, numberHorizontal, freeTop, freeBot, freeRight, freeLeft);
                break;
            }
            case ENEMY:{
                createEnemy(TEX_ENEMY, j * 32, i * 32);
                break;
            }
            case SPAWN1: {
                Entity* hero = createHero(TEX_HERO, j * 32, i * 32, SFX_ALERT, false);
                createHealthBar(100, 50, hero);
                createAmmoBar(400, 50, hero);
                createScoreBox(850, 50, hero);
                break;
            }
            case SPAWN2: {
                Entity* hero2 = createHero(TEX_HERO2, j * 32, i * 32, SFX_ALERT, true);
                createHealthBar(100, 100, hero2);
                createAmmoBar(400, 100, hero2);
                createScoreBox(850, 100, hero2);
                break;
            }
            case GOAL: {
                createVictoryZone(j * 32, i * 32);
                break;
            }
            case PU_AMMO: {
                createPowerUp(TEX_PWRUP_AMMO, j*32, i*32);
                break;
           }
            case TREE1:{
                createStaticBackgroundObject(TEX_TREE1, j*32, i*32);
                break;
            }
            case TREE2:{
                createStaticBackgroundObject(TEX_TREE2, j*32, i*32);
                break;
            }
            case BENCH:{
                createStaticBackgroundObject(TEX_BENCH, j*32, i*32);
                break;
            }
            case PU_JUMP:{
                createPowerUp(TEX_PWRUP_INFJUMP, j*32, i*32);
                break;
            }
            case PU_HEALTH:{
                createPowerUp(TEX_PWRUP_INFHEALTH, j*32, i*32);
                break;
            }
            case PU_BEER:{
                createPowerUp(TEX_PWRUP_BEER, j*32, i*32);
                break;
            }
            case FADEINTEXT:{
                createFadeInText(FONT_GLOBAL, level->getStringList().at(stringCount).c_str(),
                                 30, 255, 255, 255, 0, 900, j*32, i*32);
                stringCount++;
                break;
            }
            case NORMALTEXT:{
                createFadeInText(FONT_GLOBAL, level->getStringList().at(stringCount).c_str(),
                                 30, 255, 255, 255, 255, 900, j*32, i*32);
                stringCount++;
                break;
            }
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
        } else if (SpawnProjCommand* seCmd = dynamic_cast<SpawnProjCommand*>(*it)) {
            std::cout << "Switch Command " << seCmd->projType << std::endl;
        } else if (DespawnEntityCommand* deCmd = dynamic_cast<DespawnEntityCommand*>(*it)) {
            std::cout << "Switch Command " << deCmd->id << std::endl;
        }
    }
}
