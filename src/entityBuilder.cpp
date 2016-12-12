#include "entityBuilder.h"
#include "movementComponent.h"
#include <stdlib.h>

EntityBuilder::EntityBuilder(SDL_Renderer *renderer) :
    nextId(0),
    renderer(renderer),
    terrainTexMap(NTERRAIN, std::vector<Texture>(256)),
    fontMap(NFONT, std::vector<TTF_Font*>(256)),
    textureMap(NTEXTURE)
{
    // seed random
    srand(time(NULL));
}

/* Helper methods */
SDL_Surface* EntityBuilder::loadImage(const char* filename) {
    SDL_Surface* image = IMG_Load(filename);
    if (image == NULL) {
        std::cerr << "Load image failed! SDL_image Error: " << IMG_GetError() << std::endl;
        return NULL;
    }
    SDL_Surface* finalImage = SDL_ConvertSurface(image, image->format, 0);
    SDL_FreeSurface(image);
    if (finalImage == NULL)
        std::cerr << "Optimize image failed! SDL Error: " << SDL_GetError() << std::endl;
    return finalImage;
}

SDL_Surface* EntityBuilder::createTextSurface(FontEnum font, const char *text,
                                              int fontSize, int r, int g, int b, int a, int windowW) {
    if (!this->fontMap[font][fontSize])
        this->loadFont(font, fontSize);

    SDL_Color color={(Uint8)r,(Uint8) g,(Uint8) b, 255};
    SDL_Surface* textSurf = TTF_RenderUTF8_Blended_Wrapped(this->fontMap[font][fontSize], text, color, (Uint32)windowW);
    if (textSurf == NULL) {
        std::cerr << "Blend font failed! TTF Error: " << TTF_GetError() << std::endl;
        return NULL;
    }

    SDL_SetSurfaceAlphaMod(textSurf, (Uint8) a);
    return textSurf;
}


/* Load and free operations for texture maps */
void EntityBuilder::loadTexture(TextureEnum texType, const char* filename) {
    SDL_Surface* image = this->loadImage(filename);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, image);
    this->textureMap[texType] = {texture, image->w, image->h};
    SDL_FreeSurface(image);
}

void EntityBuilder::loadTerrain(TerrainTexEnum texType, int width) {
    SDL_Surface* image = NULL;
    if (texType == TT_BRICK) {
        image = this->loadImage("resources/tile.png");
    } else if (texType == TT_GRASS) {
        image = this->loadImage("resources/grass.png");
    } else if (texType == TT_DIRT) {
        image = this->loadImage("resources/dirt.png");
    } else if (texType == TT_SAND) {
        image = this->loadImage("resources/sand.png");
    }

    SDL_Surface* surface = SDL_CreateRGBSurface(0, image->w * width, image->h, 32,
                                                        0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    for (int i = 0; i < width; i++) {
        SDL_Rect tempRect = {image->w * i, 0, image->w, image->h};
        SDL_BlitSurface(image, NULL, surface, &tempRect);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    this->terrainTexMap[texType][width] = {texture, image->w * width, image->h};

    SDL_FreeSurface(image);
    SDL_FreeSurface(surface);
}

void EntityBuilder::loadHealthBar(int width, int height) {
    SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, width*2, height, 32, 0, 0, 0, 0);
    SDL_Rect tempRect = {0, 0, width, height};
    SDL_FillRect(tempSurface, &tempRect, SDL_MapRGB(tempSurface->format, 0, 255, 0));
    tempRect = {width, 0, width, height};
    SDL_FillRect(tempSurface, &tempRect, SDL_MapRGB(tempSurface->format, 255, 0, 0));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    this->textureMap[TEX_HEALTHBAR] = {texture, width*2, height};
}

void EntityBuilder::loadAmmoBar(int width, int height) {
    SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, width*2, height, 32, 0, 0, 0, 0);
    SDL_Rect tempRect = {0, 0, width, height};
    SDL_FillRect(tempSurface, &tempRect, SDL_MapRGB(tempSurface->format, 255, 255, 0));
    tempRect = {width, 0, width, height};
    SDL_FillRect(tempSurface, &tempRect, SDL_MapRGB(tempSurface->format, 0, 0, 0));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    this->textureMap[TEX_AMMOBAR] = {texture, width*2, height};
}

void EntityBuilder::loadFont(FontEnum fontType, int fontSize) {
    TTF_Font* font = TTF_OpenFont("resources/varsity_regular.ttf", fontSize);
    if (!font)
       std::cerr << "Load font failed! TTF Error: " << TTF_GetError() << std::endl;
    this->fontMap[fontType][fontSize] = font;   // TODO: make mapping from enum to filename
}

void EntityBuilder::freeTextures() {
    for (int i = (int) (this->textureMap.size() - 1); i >= 0; i--)
        if (this->textureMap[i].sdlTexture)
            SDL_DestroyTexture(this->textureMap[i].sdlTexture);

    for (int i = (int) (this->terrainTexMap.size() - 1); i >= 0; i--)
        for (int j = (int) (this->terrainTexMap[i].size() - 1); j >= 0; j--)
            if (this->terrainTexMap[i][j].sdlTexture)
                SDL_DestroyTexture(this->terrainTexMap[i][j].sdlTexture);
}

void EntityBuilder::freeFonts() {
    for (int i = (int) (fontMap.size() - 1); i >= 0; i--)
        for (int j = (int) (fontMap[i].size() - 1); j >= 0; j--)
            if (fontMap[i][j])
                TTF_CloseFont(fontMap[i][j]);
}

/* Entity creation operations */
Entity * EntityBuilder::createHero(TextureEnum texType, int x, int y, SfxEnum sfxType, bool wasd) {
    Texture texture = this->textureMap[texType];
    Entity* hero = new Entity(this->nextId++, x, y, 32, 62, 64, 64);
    PlaySoundCommand* command = NULL;
    if (sfxType != SFX_NONE)
        command = new PlaySoundCommand(sfxType);
    hero->collision = new HeroCollisionComponent(hero, command);
    hero->art = new AnimationComponent(hero, texture, LAYER_HERO);
    hero->input = new HeroInputComponent(hero, wasd);
    hero->score = new ScoreComponent(hero);
    hero->health = new HealthComponent(hero, 1000, new SwitchStateCommand(STATE_RESULTS));
    hero->physics = new PhysicsComponent(hero);
    hero->powerUp = new PowerUpComponent(hero);
    hero->ammo = new AmmoComponent(hero, 4);
    hero->rotates = true;
    hero->particle = new ParticleComponent(hero, new SpawnParticleCommand());
    return hero;
}

Entity* EntityBuilder::createEnemy(TextureEnum texType, int x, int y, std::vector<Entity*>* heroes) {
    Texture texture = this->textureMap[texType];
    Entity* enemy = new RespawnEntity(this->nextId++, x, y, 56, 62, 64, 64);
    enemy->collision = new EnemyCollisionComponent(enemy);
    enemy->art = new AnimationComponent(enemy, texture, LAYER_ENEMY);
    enemy->ai = new EnemyAiComponent(enemy, heroes);
    enemy->health = new HealthComponent(enemy, 200, new TempHideCommand(enemy->getId()));
    enemy->physics = new PhysicsComponent(enemy);
    enemy->physics->deceleration = 0.0f;
    enemy->physics->maxXVelocity = 0.1f;
    enemy->physics->jumpVelocity = 0.4f;
    enemy->physics->maxJumps = 1;
    enemy->particle = new ParticleComponent(enemy, new SpawnParticleCommand());
    return enemy;
}

Entity* EntityBuilder::createBackground(TextureEnum texType, int x, int y, int w, int h, float speed) {
    Texture tex = this->textureMap[texType];
    Entity* background = new Entity(this->nextId++, x, y, w, h, w, h);
    background->art = new BackgroundArtComponent(background, tex.sdlTexture, speed);
    return background;
}

Entity* EntityBuilder::createHealthBar(int x, int y, Entity* owner) {
    Texture texture = this->textureMap[TEX_HEALTHBAR];
    Entity* healthBar = new Entity(this->nextId++, x, y, texture.width/2, texture.height, texture.width/2, texture.height);
    healthBar->art = new HealthBarArtComponent(healthBar, owner, texture);
    return healthBar;
}

Entity* EntityBuilder::createHealthBarOverlay(int x, int y, TextureEnum texType) {
    Texture texture = this->textureMap[texType];
    Entity* healthBarOverlay = new Entity(this->nextId++, x, y, texture.width, texture.height, texture.width, texture.height);
    healthBarOverlay->art = new StaticArtComponent(healthBarOverlay, texture.sdlTexture, LAYER_HUD2, true);
    return healthBarOverlay;
}

Entity* EntityBuilder::createAmmoBar(int, int, Entity* owner) {
    Texture texture = this->textureMap[TEX_AMMOBAR];
    Entity* ammoBar = new Entity(this->nextId++, owner->x, owner->y, texture.width / 2, texture.height, texture.width / 2, texture.height);
    ammoBar->art = new AmmoBarArtComponent(ammoBar, owner, texture);
    return ammoBar;
}

// Entity* EntityBuilder::createScoreBox(int x, int y, Entity* owner, FontEnum fontType, int fontSize) {
//     if (!this->fontMap[fontType][fontSize])
//         this->loadFont(fontType, fontSize);
//     Entity* scoreBox = new Entity(this->nextId++, x, y, 100, 100, 100, 100);
//     scoreBox->art = new ScoreTextArtComponent(scoreBox, this->renderer,
//                                               this->fontMap[fontType][fontSize], owner->score, 2);
//     return scoreBox;
// }

Entity* EntityBuilder::createFadeInText(FontEnum fontType, const char *text, int fontSize,
                                        int r, int g, int b, int initialAlpha,
                                        int windowW, int x, int y) {
    SDL_Surface* textSurface = this->createTextSurface(fontType, text, fontSize, r, g, b, initialAlpha, windowW);
    Entity * fadeInText = new Entity(this->nextId++, x, y, textSurface->w, textSurface->h, textSurface->w, textSurface->h);
    fadeInText->art = new TextFadeInComponent(fadeInText, this->renderer, textSurface, initialAlpha);
    return fadeInText;
}

Entity* EntityBuilder::createHorizontallyCenteredFadeInMenuText(FontEnum fontType, const char *text, int fontSize,
                                                                int r, int g, int b, int initialAlpha,
                                                                int windowW, int yPos,
                                                                int index, int numOptions, StateEnum nextState) {
    SDL_Surface* textSurface = this->createTextSurface(fontType, text, fontSize, r, g, b, initialAlpha, windowW);
    int x = (windowW/2 - textSurface->w/2);
    Entity* fadeInText = new Entity(this->nextId++, x, yPos, textSurface->w, textSurface->h, textSurface->w, textSurface->h);
    fadeInText->art = new TextFadeInComponent(fadeInText, this->renderer, textSurface, initialAlpha);
    SwitchStateCommand* nextStateCmd = NULL;
    if (nextState != STATE_NONE)
        nextStateCmd = new SwitchStateCommand(nextState);
    fadeInText->input = new MenuOptionInputComponent(fadeInText, index, numOptions, nextStateCmd);
    return fadeInText;
}

Entity* EntityBuilder::createHorizontallyCenteredSelectLevelText(FontEnum fontType, const char *text, int fontSize,
                                                                 int r, int g, int b, int initialAlpha, int windowW,
                                                                 int yPos, int index, int numOptions,
                                                                 StateEnum nextState, bool *levelSelected) {
    SDL_Surface* textSurface = this->createTextSurface(fontType, text, fontSize, r, g, b, initialAlpha, windowW);
    int x = (windowW/2 - textSurface->w/2);
    Entity* fadeInText = new Entity(this->nextId++, x, yPos, textSurface->w, textSurface->h, textSurface->w, textSurface->h);
    fadeInText->art = new TextFadeInComponent(fadeInText, this->renderer, textSurface, initialAlpha);
    SwitchStateCommand* nextStateCmd = NULL;
    if (nextState != STATE_NONE)
        nextStateCmd = new SwitchStateCommand(nextState);
    fadeInText->input = new LevelSelectInputComponent(fadeInText, index, numOptions, nextStateCmd, levelSelected);
    return fadeInText;
}

Entity* EntityBuilder::createLevelPreview(TextureEnum tex, int x, int y) {
    Texture texture = this->textureMap[tex];
    Entity* entity = new Entity(this->nextId++, x, y, 600, 100, 600, 100);
    entity->art = new StaticArtComponent(entity, texture.sdlTexture, LAYER_TEXT, false);
    return entity;
}

Entity* EntityBuilder::createVictoryZone(int x, int y) {        // not using maps, since its a
    Entity* zone = new Entity(this->nextId++, x, y, 50, 50, 50, 50);    // temporary feature
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);
    SDL_Rect tempRect = {0,0,50,50};
    SDL_FillRect(surface, &tempRect, SDL_MapRGB(surface->format, 255, 0, 0));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface);
    zone->art = new StaticArtComponent(zone, texture, LAYER_TERRAIN2, false);
    zone->collision = new VictoryZoneCollisionComponent(zone, new SwitchStateCommand(STATE_MENU));
    return zone;
}

Entity* EntityBuilder::createPowerUp(TextureEnum pwrUpType, SfxEnum pwrSound, int x, int y) {
    Texture texture = this->textureMap[pwrUpType];
    Entity *entity = new Entity(this->nextId++, x, y, 30, 30, 30, 30);
    entity->art = new StaticArtComponent(entity, texture.sdlTexture, LAYER_TERRAIN2, false);
    entity->collision = new PowerUpCollisionComponent(entity, pwrUpType, pwrSound);
    return entity;
}

Entity* EntityBuilder::createPowerUpOverlay(TextureEnum pwrUpType, int x, int y, Entity* owner, int index) {
    Texture texture = this->textureMap[pwrUpType];
    Entity* entity = new Entity(this->nextId++, x, y, 32, 64, 64, 64);
    LayerEnum layer = (pwrUpType == TEX_PWRUP_INFJUMP_OVERLAY ? LAYER_UNDERLAY : LAYER_OVERLAY);
    entity->art = new PowerUpArtComponent(entity, owner, texture, layer, index);
    return entity;
}

Entity* EntityBuilder::createStaticBackgroundObject(TextureEnum texType, int x, int y) {
    Texture texture = this->textureMap[texType];
    Entity* object = new Entity(this->nextId++, x, y, texture.width, texture.height, texture.width, texture.height);
    object->art = new StaticArtComponent(object, texture.sdlTexture, LAYER_FG, false);
    return object;
}

Entity* EntityBuilder::createAnimatedBackgroundObject(TextureEnum texType, int x, int y, int fps, int numFrames) {
    Texture texture = this->textureMap[texType];
    Entity* object = new Entity(this->nextId++, x, y, texture.width/numFrames, texture.height, texture.width/numFrames, texture.height);
    object->art = new ObjectAnimationComponent(object, texture.sdlTexture, LAYER_FG, false, fps, numFrames);
    return object;
}

/***
Entity* EntityBuilder::createStaticBackgroundObject(TextureEnum texType, TextureEnum lightType, int x, int y) {
    Texture texture = this->textureMap[texType];
    Entity* object = new Entity(this->nextId++, x, y, texture.width, texture.height, texture.width, texture.height);
    object->art = new StaticArtComponent(object, texture.sdlTexture, LAYER_FG, false);
    object->art->setLightTexture(&this->textureMap[lightType]);
    return object;
}
 ***/


Entity* EntityBuilder::createTerrain(TerrainTexEnum texType, int x, int y, int numberHorizontal,
        bool freeTop, bool freeBot, bool freeRight, bool freeLeft) {
    if (!this->terrainTexMap[texType][numberHorizontal].sdlTexture)
        this->loadTerrain(texType, numberHorizontal);
    Texture texture = this->terrainTexMap[texType][numberHorizontal];

    Entity* terrain = new Entity(this->nextId++, x, y, texture.width, texture.height, texture.width, texture.height);
    terrain->art = new StaticArtComponent(terrain, texture.sdlTexture, LAYER_TERRAIN1, false);
    terrain->collision = new TerrainCollisionComponent(terrain, freeTop, freeBot, freeRight, freeLeft);
    return terrain;
}

Entity* EntityBuilder::createBounce(TextureEnum texType, int x, int y) {
    Texture texture = this->textureMap[texType];
    // set the drawing offset
    Entity* entity = new Entity(this->nextId++, x, y + 24, 32, 8, 32, 32);
    entity->drawY -= 12;
    entity->art = new BounceAnimationComponent(entity, texture);
    entity->collision = new BounceCollisionComponent(entity);
    return entity;
}

Entity* EntityBuilder::createFadingTerrain(TerrainTexEnum texType, int x, int y, int numberHorizontal, bool freeTop,
                                           bool freeBot, bool freeRight, bool freeLeft) {
    if (!this->terrainTexMap[texType][numberHorizontal].sdlTexture)
        this->loadTerrain(texType, numberHorizontal);
    Texture texture = this->terrainTexMap[texType][numberHorizontal];
    Entity* terrain = new Entity(this->nextId++, x, y, texture.width, texture.height, texture.width, texture.height);

    terrain->art = new FadingTerrainArtComponent(terrain, texture.sdlTexture);
    terrain->collision = new FadingTerrainColComponent(terrain, freeTop, freeBot, freeRight, freeLeft);
    return terrain;
}

Entity* EntityBuilder::createProjectile(TextureEnum texType, int x, int y, float charge, int dir, int ownerId, Entity * closest) {
    Texture texture = this->textureMap[texType];
    Entity* projectile = new Entity(this->nextId++, x, y, 20, 20, texture.width, texture.height);
    projectile->rotates = true;
    projectile->art = new ProjectileArtComponent(projectile, texture.sdlTexture);
    DespawnEntityCommand* dCmd = new DespawnEntityCommand(projectile->getId());
    projectile->collision = new ProjectileCollisionComponent(projectile, dCmd, ownerId);
    projectile->physics = new PhysicsComponent(projectile);
    projectile->physics->xVelocity = dir * charge * 0.7f;
    projectile->physics->maxXVelocity = 0.7f;
    projectile->physics->yVelocity = -0.4f;
    projectile->physics->deceleration = 0.0f;
    projectile->physics->target = closest;
    projectile->particle = new ParticleComponent(projectile, new SpawnParticleCommand());
    return projectile;
}

Entity* EntityBuilder::createParticle(TextureEnum texType, int x, int y) {
    Texture texture = this->textureMap[texType];
    Entity* particle = new Entity(this->nextId++, x, y, 20, 20, 20, 20);
    particle->art = new ParticleAnimationComponent(particle, texture);
    particle->physics = new MovementComponent(particle);
    particle->physics->xVelocity = 0.01 * (rand() % 20 - 10);
    particle->physics->yVelocity = 0.01 * (rand() % 20 - 10);
    return particle;
}

Entity* EntityBuilder::createBomb(TextureEnum texType, int x, int y, float charge, int dir, Entity* closest) {
    Texture texture = this->textureMap[texType];
    Texture animation = this->textureMap[TEX_PWRUP_BOMB];
    Entity* projectile = new Entity(this->nextId++, x, y, 20, 20, 32, 32);
    projectile->rotates = true;
    projectile->art = new OneTimeAnimationComponent(projectile, animation, LAYER_HERO, 1500, 1, texture);
    projectile->collision = new BombCollisionComponent(projectile);
    projectile->physics = new PhysicsComponent(projectile);
    projectile->physics->xVelocity = dir * charge * 0.7f;
    projectile->physics->maxXVelocity = 0.7f;
    projectile->physics->yVelocity = -0.4f;
    projectile->physics->deceleration = 0.0f;
    projectile->physics->target = closest;
    projectile->particle = new ParticleComponent(projectile, new SpawnParticleCommand());
    projectile->particle->setIndefSpawn(true);
    return projectile;
}

void EntityBuilder::setLightTexture(Entity *entity, TextureEnum lightTex, bool addTrueModFalse) {
    entity->art->setLightTexture(&textureMap[lightTex], addTrueModFalse);
}
