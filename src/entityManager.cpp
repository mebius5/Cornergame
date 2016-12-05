#include "entityManager.h"

EntityManager::EntityManager(SDL_Renderer* renderer, std::vector<Command*>& cmdList, int windowW) :
        commandList(cmdList),
        entityBuilder(renderer),
        windowW(windowW),
        numCleanable(0) {
    this->initIndices();
    this->entityBuilder.loadTexture(TEX_HERO, "spritesheets/hero.png");
    this->entityBuilder.loadTexture(TEX_HERO2, "spritesheets/hero2.png");
    this->entityBuilder.loadTexture(TEX_ENEMY, "spritesheets/lax.png");
    this->entityBuilder.loadTexture(TEX_PROJECTILE, "spritesheets/ball.png");
    this->entityBuilder.loadTexture(TEX_BOUNCE, "spritesheets/bounce.png");
    this->entityBuilder.loadTexture(TEX_PWRUP_INFHEALTH, "resources/star.png");
    this->entityBuilder.loadTexture(TEX_PWRUP_INFHEALTH_OVERLAY, "resources/starOverlay.png");
    this->entityBuilder.loadTexture(TEX_PWRUP_INFJUMP, "resources/wings.png");
    this->entityBuilder.loadTexture(TEX_PWRUP_INFJUMP_OVERLAY, "resources/wingsOverlay.png");
    this->entityBuilder.loadTexture(TEX_PWRUP_AMMO, "resources/paper.png");
    this->entityBuilder.loadTexture(TEX_PWRUP_BEER, "resources/beer.png");
    this->entityBuilder.loadTexture(TEX_PWRUP_BEER_OVERLAY, "resources/beerOverlay.png");
    this->entityBuilder.loadTexture(TEX_TREE1, "resources/greentree1.png");
    this->entityBuilder.loadTexture(TEX_TREE2, "resources/greentree2.png");
    this->entityBuilder.loadTexture(TEX_BENCH, "resources/bench.png");
    this->entityBuilder.loadTexture(TEX_LEVEL1_PREVIEW, "resources/level1preview.png");
    this->entityBuilder.loadTexture(TEX_LEVEL2_PREVIEW, "resources/level2preview.png");
    this->entityBuilder.loadTexture(TEX_LEVEL3_PREVIEW, "resources/level3preview.png");
    this->entityBuilder.loadTexture(TEX_LEVEL4_PREVIEW, "resources/level4preview.png");
    this->entityBuilder.loadTexture(TEX_BACKGROUND1, "resources/background1.png");
    this->entityBuilder.loadTexture(TEX_BACKGROUND2, "resources/background2.png");
    this->entityBuilder.loadTexture(TEX_BACKGROUND3, "resources/background3.png");
    this->entityBuilder.loadTexture(TEX_DARKBACKGROUND1, "resources/greyBackground1.png");
    this->entityBuilder.loadTexture(TEX_DARKBACKGROUND2, "resources/greyBackground2.png");
    this->entityBuilder.loadTexture(TEX_TORCH,"resources/torch.png");
    this->entityBuilder.loadTexture(TEX_LIGHT_ADD_128_FIRE,"resources/light_fire_add_128.png");
    this->entityBuilder.loadTexture(TEX_LIGHT_ADD_600_HERO,"resources/light_add_600_hero.png");
    this->entityBuilder.loadTexture(TEX_LIGHT_MOD_GLOBAL, "resources/light_mod_global.png");
    this->entityBuilder.loadHealthBar(200, 40);
    this->entityBuilder.loadAmmoBar(50, 8);
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
        this->artComponents.push_back(NULL);        // add one space
        int layer = entity->art->layer;
        for (int i = NLAYERS-1; i > layer; i--) {
            this->layerIndices[i]++;                // shift first layer element to last layer element
            this->artComponents[this->layerIndices[i]] = this->artComponents[this->layerIndices[i-1]+1];
        }
        this->layerIndices[layer]++;                // insert new artComp
        this->artComponents[this->layerIndices[layer]] = entity->art;
        if (BackgroundArtComponent* bg = dynamic_cast<BackgroundArtComponent*>(entity->art))
            this->bgComponents.push_back(bg);
    }
    if (entity->collision) {
        if (StaticCollisionComponent* scc =
                dynamic_cast<StaticCollisionComponent*>(entity->collision)) {
            this->staticCollisionComponents.push_back(scc);

            if(PowerUpCollisionComponent * puc = dynamic_cast<PowerUpCollisionComponent*>(entity->collision)){
                this->powerUpCollisionComponents.push_back(puc);
            }

            if(FadingTerrainColComponent * ftc = dynamic_cast<FadingTerrainColComponent*>(entity->collision)){
                this->fadingTerrainColComponents.push_back(ftc);
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

void EntityManager::initIndices() {
    for (int i = 0; i < NLAYERS; i++)
        this->layerIndices[i] = -1;
}

void EntityManager::initRespawns() {
    std::unordered_map<int, Entity*>::const_iterator it;
    for (it = this->entityMap.begin(); it != this->entityMap.end(); ++it)
        if (RespawnEntity* entity = dynamic_cast<RespawnEntity*>(it->second))
            this->respawnEntities.push_back(entity);
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

    this->numCleanable = (int) this->deletionQueue.size();
}

void EntityManager::clear() {
    this->cleanupEntities();    // delete all Entities from deletionQueue
    std::vector<RespawnEntity*>::const_iterator ents;
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
    this->bgComponents.clear();
    this->inputComponents.clear();
    this->physicsComponents.clear();
    this->healthComponents.clear();
    this->scoreComponents.clear();
    this->staticCollisionComponents.clear();
    this->dynamicCollisionComponents.clear();
    this->powerUpComponents.clear();
    this->powerUpCollisionComponents.clear();
    this->fadingTerrainColComponents.clear();
    this->heroEntities.clear();
    this->respawnEntities.clear();
    this->initIndices();
}

/* Entity Creation Methods */
Entity * EntityManager::createHero(TextureEnum texType, int x, int y, SfxEnum sfxType, bool wasd) {
    Entity* entity = this->entityBuilder.createHero(texType, x, y, sfxType, wasd);
    this->addEntity(entity);
    this->heroEntities.push_back(entity);
    Entity *pwr1 = this->entityBuilder.createPowerUpOverlay(TEX_PWRUP_INFJUMP_OVERLAY, x, y, entity, TEX_PWRUP_INFJUMP);
    this->addEntity(pwr1);
    Entity *pwr2 = this->entityBuilder.createPowerUpOverlay(TEX_PWRUP_INFHEALTH_OVERLAY, x, y, entity, TEX_PWRUP_INFHEALTH);
    this->addEntity(pwr2);
    Entity *pwr4 = this->entityBuilder.createPowerUpOverlay(TEX_PWRUP_BEER_OVERLAY, x, y, entity, TEX_PWRUP_BEER);
    this->addEntity(pwr4);
    return entity;
}

Entity* EntityManager::createEnemy(TextureEnum texType, int x, int y) {
    Entity* entity = this->entityBuilder.createEnemy(texType, x, y, &this->heroEntities);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createBackground(TextureEnum texType, int x, int y, int w, int h,float speed) {
    Entity* entity = this->entityBuilder.createBackground(texType, x, y, w, h, speed);
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

// Entity* EntityManager::createScoreBox(int x, int y, Entity* owner) {
//     Entity* entity = this->entityBuilder.createScoreBox(x, y, owner, FONT_GLOBAL, 32);
//     this->addEntity(entity);
//     return entity;
// }

void EntityManager::createFadeInText(FontEnum font,
                                     const char* text, int fontSize, int r, int g, int b,
                                     int initialAlpha, int windowW, int x, int y) {
    std::string tempText = text;
    std::string::size_type  i=0;
    int yOffset=0;
    while((i = tempText.find("\n"))!=std::string::npos){
        Entity * entity = this->entityBuilder.createFadeInText(
                font, tempText.substr(0,i).c_str(), fontSize, r, g, b, initialAlpha, windowW, x, y+yOffset);
        this->addEntity(entity);
        tempText = tempText.substr(i+1, tempText.length());
        yOffset += entity->drawHeight;
    }
    if(tempText.length()!=0){
        Entity * entity = this->entityBuilder.createFadeInText(
                font, tempText.c_str(), fontSize, r, g, b, initialAlpha, windowW, x, y+yOffset);
        this->addEntity(entity);
    }
}

void EntityManager::createCenteredFadeInText(FontEnum font,
                                             const char* text, int fontSize, int r, int g, int b,
                                             int initialAlpha, int windowW, int windowH) {
    std::string tempText = text;
    std::string::size_type  i=0;
    int yOffset=0;
    while((i = tempText.find("\n"))!=std::string::npos){
        Entity * entity = this->entityBuilder.createFadeInText(
                font, tempText.substr(0,i).c_str(), fontSize, r, g, b, initialAlpha, windowW, 0, 0);
        entity->x = (windowW/2 - entity->width/2);
        entity->y = (windowH/2 - entity->height/2)+yOffset;
        this->addEntity(entity);
        tempText = tempText.substr(i+1, tempText.length());
        yOffset += entity->drawHeight;
    }
    if(tempText.length()!=0){
        Entity * entity = this->entityBuilder.createFadeInText(
                font, tempText.c_str(), fontSize, r, g, b, initialAlpha, windowW, 0, 0);
        entity->x = (windowW/2 - entity->width/2);
        entity->y = (windowH/2 - entity->height/2)+yOffset;
        this->addEntity(entity);
    }
}

void EntityManager::createHorizontallyCenteredFadeInText(FontEnum font, const char *text, int fontSize, int r, int g,
                                                         int b, int initialAlpha, int windowW, int yPos) {
    std::string tempText = text;
    std::string::size_type  i=0;
    int yOffset=0;
    while((i = tempText.find("\n"))!=std::string::npos){
        Entity * entity = this->entityBuilder.createFadeInText(
                font, tempText.substr(0,i).c_str(), fontSize, r, g, b, initialAlpha, windowW, 0, yPos+yOffset);
        entity->x = (windowW/2 - entity->width/2);
        this->addEntity(entity);
        tempText = tempText.substr(i+1, tempText.length());
        yOffset += entity->drawHeight;
    }
    if(tempText.length()!=0){
        Entity * entity = this->entityBuilder.createFadeInText(
                font, tempText.c_str(), fontSize, r, g, b, initialAlpha, windowW, 0, yPos+yOffset);
        entity->x = (windowW/2 - entity->width/2);
        this->addEntity(entity);
    }
}

Entity* EntityManager::createHorizontallyCenteredFadeInMenuText(FontEnum font, const char *text,
                                                                int fontSize,
                                                                int r, int g, int b, int initialAlpha,
                                                                int windowW, int yPos,
                                                                int index, int numOptions, StateEnum nextState) {
    std::string tempText = text;
    std::string::size_type  i=0;
    int yOffset=0;
    while((i = tempText.find("\n"))!=std::string::npos){
        Entity* entity = this->entityBuilder.createHorizontallyCenteredFadeInMenuText(
                font, tempText.substr(0,i).c_str(), fontSize, r, g, b, initialAlpha,
                windowW, yPos+yOffset, index, numOptions, nextState);
        this->addEntity(entity);
        tempText = tempText.substr(i+1, tempText.length());
        yOffset += entity->drawHeight;
    }
    if(tempText.length()!=0){
        Entity* entity = this->entityBuilder.createHorizontallyCenteredFadeInMenuText(
                font, tempText.c_str(), fontSize, r, g, b, initialAlpha,
                windowW, yPos+yOffset, index, numOptions, nextState);
        this->addEntity(entity);
        return entity;
    }
    return NULL;
}

Entity* EntityManager::createHorizontallyCenteredSelectLevelText(FontEnum fontType, const char *text, int fontSize,
                                                                 int r, int g, int b, int initialAlpha, int windowW,
                                                                 int yPos, int index, int numOptions,
                                                                 StateEnum nextState, bool *levelSelected) {
    std::string tempText = text;
    std::string::size_type  i=0;
    int yOffset=0;
    while((i = tempText.find("\n"))!=std::string::npos){
        Entity* entity = this->entityBuilder.createHorizontallyCenteredSelectLevelText(
                fontType, tempText.substr(0,i).c_str(), fontSize, r, g, b, initialAlpha,
                windowW, yPos+yOffset, index, numOptions, nextState, levelSelected);
        this->addEntity(entity);
        tempText = tempText.substr(i+1, tempText.length());
        yOffset += entity->drawHeight;
    }
    if(tempText.length()!=0){
        Entity* entity = this->entityBuilder.createHorizontallyCenteredSelectLevelText(
                fontType, tempText.c_str(), fontSize, r, g, b, initialAlpha,
                windowW, yPos+yOffset, index, numOptions, nextState, levelSelected);
        this->addEntity(entity);
        return entity;
    }
    return NULL;
}


Entity* EntityManager::createLevelPreview(TextureEnum tex, int x, int y) {
    Entity* entity = this->entityBuilder.createLevelPreview(tex, x, y);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createVictoryZone(int x, int y) {
    Entity* entity = this->entityBuilder.createVictoryZone(x, y);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createPowerUp(TextureEnum pwrUpType, SfxEnum pwrSound, int x, int y) {
    Entity * entity = this->entityBuilder.createPowerUp(pwrUpType, pwrSound, x, y);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createStaticBackgroundObject(TextureEnum texType, int x, int y) {
    Entity* entity = this->entityBuilder.createStaticBackgroundObject(texType, x,y);
    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createAnimatedBackgroundObject(TextureEnum texType, int x, int y, int fps, int numFrames) {
    Entity* entity = this->entityBuilder.createAnimatedBackgroundObject(texType, x,y, fps, numFrames);
    this->addEntity(entity);
    return entity;
}

/***
Entity* EntityManager::createStaticBackgroundObject(TextureEnum texType, TextureEnum lightType, int x, int y) {
    Entity* entity = this->entityBuilder.createStaticBackgroundObject(texType, lightType, x,y);
    this->addEntity(entity);
    return entity;
}
 ***/

Entity* EntityManager::createTerrain(Tile tileType, int x, int y, int numberHorizontal, bool freeTop,
                                     bool freeBot, bool freeRight, bool freeLeft) {
    TerrainTexEnum texType = (TerrainTexEnum)tileType;
    Entity * entity;
    if(texType!=TT_SAND){
        entity = this->entityBuilder.createTerrain(
                texType, x, y, numberHorizontal, freeTop, freeBot, freeRight, freeLeft);
    } else{
        entity = this->entityBuilder.createFadingTerrain(
                texType, x, y, numberHorizontal, freeTop, freeBot, freeRight, freeLeft);
    }

    this->addEntity(entity);
    return entity;
}

Entity* EntityManager::createBounce(TextureEnum texType, int x, int y) {
    Entity* entity = this->entityBuilder.createBounce(texType, x, y);
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
            sqnorm = (float) (pow(hpEntity->x - x, 2) + pow(hpEntity->y - y, 2));
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
            for (pu = this->powerUpCollisionComponents.begin(); pu != this->powerUpCollisionComponents.end(); ++pu) {
                (*pu)->setIsClaimed(false);
                (*pu)->entity->art->isVisible = true;
            }

            std::vector<FadingTerrainColComponent*>::iterator ft;
            for (ft = this->fadingTerrainColComponents.begin(); ft != this->fadingTerrainColComponents.end(); ++ft){
                (*ft)->resetComponent();
                if(FadingTerrainArtComponent * fta = dynamic_cast<FadingTerrainArtComponent*>((*ft)->entity->art)){
                    fta->resetComponent();
                }
            }

            std::vector<RespawnEntity*>::iterator ents;
            for (ents = this->respawnEntities.begin(); ents != this->respawnEntities.end(); ++ents) {
                RespawnEntity* entity = *ents;
                if (this->entityMap.count(entity->getId()) == 0) {
                    entity->validate();
                    this->addEntity(entity);
                    entity->x = entity->initialX;
                    entity->y = entity->initialY;
                } else if (entity->x + entity->width <= 0)
                    entity->x += 2 * this->windowW + (rand() % 100);
                else if (entity->x < this->windowW && !entity->shifted)
                    entity->x = this->windowW + (rand() % 100);
                entity->shifted = false;
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
                case TILE_DIRT:
                case TILE_BRICK:
                case TILE_GRASS: {
                    bool freeLeft = (j == 0 || level->getTile(i, j-1) >= TILE_NONE);
                    bool freeRight;     // assigned value later
                    bool freeTop = (i == 0 || level->getTile(i-1, j) >= TILE_NONE);
                    bool freeBot = (i == level->contentHeight-1 || level->getTile(i+1, j) >= TILE_NONE);
                    int numberHorizontal = 1;
                    int originalJ = j;
                    // create horizontal slabs, breaking at each intersection with other terrain rectangles.
                    while (j < (level->width-1) && level->getTile(i, j+1) == level->getTile(i, j)) {
                        if (i > 0 && freeTop && level->getTile(i-1, j+1) < TILE_NONE)
                            break;
                        if (i > 0 && !freeTop && level->getTile(i-1, j+1) >= TILE_NONE)
                            break;
                        if (i < level->contentHeight-1 && freeBot && level->getTile(i+1, j+1) < TILE_NONE)
                            break;
                        if (i < level->contentHeight-1 && !freeBot && level->getTile(i+1, j+1) >= TILE_NONE)
                            break;
                        numberHorizontal++;
                        j++;
                    }
                    freeRight = (j == level->contentWidth-1 || level->getTile(i, j+1) >= TILE_NONE);
                    createTerrain(level->getTile(i, j), originalJ*32, i*32, numberHorizontal, freeTop, freeBot, freeRight, freeLeft);
                    break;
                }
                case TILE_SAND: {
                    bool freeLeft = (j == 0 || level->getTile(i, j-1) >= TILE_NONE);
                    bool freeRight;     // assigned value later
                    bool freeTop = (i == 0 || level->getTile(i-1, j) >= TILE_NONE);
                    bool freeBot = (i == level->contentHeight-1 || level->getTile(i+1, j) >= TILE_NONE);
                    int numberHorizontal = 1;
                    int originalJ = j;
                    freeRight = (j == level->contentWidth-1 || level->getTile(i, j+1) >= TILE_NONE);
                    createTerrain(level->getTile(i, j), originalJ*32, i*32, numberHorizontal, freeTop, freeBot, freeRight, freeLeft);
                    break;
                }
                case TILE_BOUNCE:
                    createBounce(TEX_BOUNCE, j * 32, i * 32);
                    break;
                case TILE_ENEMY:
                    createEnemy(TEX_ENEMY, j * 32, i * 32);
                    break;
                case TILE_SPAWN1: {
                    Entity* hero = createHero(TEX_HERO, j * 32, i * 32, SFX_ALERT, false);
                    createHealthBar(100, 50, hero);
                    createAmmoBar(400, 50, hero);
                    break;
                }
                case TILE_SPAWN2: {
                    Entity* hero2 = createHero(TEX_HERO2, j * 32, i * 32, SFX_ALERT, true);
                    createHealthBar(100, 100, hero2);
                    createAmmoBar(400, 100, hero2);
                    break;
                }
                case TILE_GOAL:
                    createVictoryZone(j * 32, i * 32);
                    break;
                case TILE_PU_AMMO:
                    createPowerUp(TEX_PWRUP_AMMO, SFX_AMMO, j*32, i*32);
                    break;
                case TILE_TREE1:
                    createStaticBackgroundObject(TEX_TREE1, j*32, i*32);
                    break;
                case TILE_TREE2:
                    createStaticBackgroundObject(TEX_TREE2, j*32, i*32);
                    break;
                case TILE_BENCH:
                    createStaticBackgroundObject(TEX_BENCH, j*32, i*32);
                    break;
                case TILE_TORCH:{
                    Entity * entity = createAnimatedBackgroundObject(TEX_TORCH, j*32, i*32, 2, 5);
                    setLightTexture(entity,TEX_LIGHT_ADD_128_FIRE, true);
                    break;
                }
                case TILE_PU_JUMP:
                    createPowerUp(TEX_PWRUP_INFJUMP, SFX_WOOSH, j*32, i*32);
                    break;
                case TILE_PU_HEALTH:
                    createPowerUp(TEX_PWRUP_INFHEALTH, SFX_ARMOR, j*32, i*32);
                    break;
                case TILE_PU_BEER:
                    createPowerUp(TEX_PWRUP_BEER, SFX_DRINK, j*32, i*32);
                    break;
                case TILE_FADEINTEXT:
                    createFadeInText(FONT_GLOBAL, level->getStringList()[stringCount].c_str(),
                                     30, 255, 255, 255, 0, windowW, j*32, i*32);
                    stringCount++;
                    break;
                case TILE_NORMALTEXT:
                    createFadeInText(FONT_GLOBAL, level->getStringList()[stringCount].c_str(),
                                     30, 0, 0, 0, 255, windowW, j*32, i*32);
                    stringCount++;
                    break;
                default:
                    break;
            }
        }
    }
}

void EntityManager::setLightTexture(Entity *entity, TextureEnum lightTex, bool addTrueModFalse) {
    this->entityBuilder.setLightTexture(entity,lightTex,addTrueModFalse);
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
