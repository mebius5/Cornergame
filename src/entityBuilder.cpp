#include "entityBuilder.h"

EntityBuilder::EntityBuilder(SDL_Renderer* renderer) :
    nextId(0),
    renderer(renderer),
    textureMap(10),
    terrainTexMap(1, std::vector<Texture>(256)),
    fontMap(1, std::vector<TTF_Font*>(128)) {
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

SDL_Surface* EntityBuilder::createText(FontEnum fontType, const char* text,
                                       int fontSize, int r, int g, int b, int a) {
    if (!this->fontMap[fontType][fontSize])
        this->loadFont(fontType, fontSize);

    SDL_Color color={(Uint8)r,(Uint8) g,(Uint8) b, 255};
    SDL_Surface* textSurf = TTF_RenderUTF8_Blended(this->fontMap[fontType][fontSize], text, color);
    if (textSurf == NULL) {
       std::cerr << "Blend font failed! TTF Error: " << TTF_GetError() << std::endl;
       return NULL;
    }

    SDL_SetSurfaceAlphaMod(textSurf, a);
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
    SDL_Surface* image = this->loadImage("resources/tile.png"); // TODO: make mapping!
    SDL_Surface* surface = SDL_CreateRGBSurface(0, image->w * width, image->h, 32, 0, 0, 0, 0);
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

void EntityBuilder::loadFont(FontEnum fontType, int fontSize) {
    TTF_Font* font = TTF_OpenFont("resources/CaesarDressing-Regular.ttf", fontSize);
    if (!font)
       std::cerr << "Load font failed! TTF Error: " << TTF_GetError() << std::endl;
    this->fontMap[fontType][fontSize] = font;   // TODO: make mapping from enum to filename
}

void EntityBuilder::freeTextures() {
    for (int i = this->textureMap.size()-1; i >= 0; i--)
        if (this->textureMap[i].sdlTexture)
            SDL_DestroyTexture(this->textureMap[i].sdlTexture);

    for (int i = this->terrainTexMap.size()-1; i >= 0; i--)
        for (int j = this->terrainTexMap[i].size()-1; j >= 0; j--)
            if (this->terrainTexMap[i][j].sdlTexture)
                SDL_DestroyTexture(this->terrainTexMap[i][j].sdlTexture);
}

void EntityBuilder::freeFonts() {
    for (int i = fontMap.size()-1; i >= 0; i--)
        for (int j = fontMap[i].size()-1; j >= 0; j--)
            if (fontMap[i][j])
                TTF_CloseFont(fontMap[i][j]);
}

/* Entity creation operations */
Entity* EntityBuilder::createHero(TextureEnum texType, int x, int y, SfxEnum sfxType, bool wasd) {
    Texture texture = this->textureMap[texType];
    Entity* hero = new Entity(this->nextId++, x, y, 32, 64, 64, 64);

    PlaySoundCommand* command = NULL;
    if (sfxType != SFX_NONE)
        command = new PlaySoundCommand(sfxType);
    hero->collision = new HeroCollisionComponent(hero, command);
    hero->art = new AnimationComponent(hero, texture, 1);
    hero->input = new HeroInputComponent(hero, wasd, new SpawnEntityCommand(PROJ_HERO));
    hero->score = new ScoreComponent(hero);
    hero->health = new HealthComponent(hero, 1000, new SwitchStateCommand(STATE_RESULTS));
    hero->physics = new PhysicsComponent(hero);
    return hero;
}

Entity* EntityBuilder::createEnemy(TextureEnum texType, int x, int y, std::vector<Entity*>* heroes) {
    Texture texture = this->textureMap[texType];
    Entity* enemy = new Entity(this->nextId++, x, y, 64, 64, 64, 64);
    enemy->collision = new EnemyCollisionComponent(enemy);
    enemy->art = new AnimationComponent(enemy, texture, 1);
    enemy->ai = new EnemyAiComponent(enemy, heroes);
    enemy->health = new HealthComponent(enemy, 200, new DespawnEntityCommand(enemy->getId()));
    enemy->physics = new PhysicsComponent(enemy);
    enemy->physics->deceleration = 0.0f;
    enemy->physics->maxVelocity = 0.1f;
    enemy->physics->maxJumps = 1;
    return enemy;
}

Entity* EntityBuilder::createBackground(TextureEnum texType, int width, int height) {
    Texture texture = this->textureMap[texType];
    Entity* background = new Entity(this->nextId++, 0, 0, width, height, width, height);
    background->art = new StaticArtComponent(background, texture.sdlTexture, 0, true);
    return background;
}

Entity* EntityBuilder::createHealthBar(int x, int y, Entity* owner) {
    Texture texture = this->textureMap[TEX_HEALTHBAR];
    Entity* healthBar = new Entity(this->nextId++, x, y, texture.width / 2, texture.height, texture.width / 2, texture.height);
    healthBar->art = new HealthBarArtComponent(healthBar, texture, owner->health, 2);
    return healthBar;
}

Entity* EntityBuilder::createScoreBox(int x, int y, Entity* owner, FontEnum fontType, int fontSize) {
    if (!this->fontMap[fontType][fontSize])
        this->loadFont(fontType, fontSize);
    Entity* scoreBox = new Entity(this->nextId++, x, y, 100, 100, 100, 100);
    scoreBox->art = new ScoreTextArtComponent(scoreBox, this->renderer,
                                              this->fontMap[fontType][fontSize], owner->score, 2);
    return scoreBox;
}

Entity* EntityBuilder::createCenteredFadeInText(FontEnum fontType, const char *text, int fontSize,
                                                int r, int g, int b, int initialAlpha,
                                                int windowW, int windowH) {
    if (!this->fontMap[fontType][fontSize])
        this->loadFont(fontType, fontSize);
    SDL_Surface* textSurface =
        this->createText(fontType, text, fontSize, r, g, b, initialAlpha);
    int x = (windowW/2 - textSurface->w/2);
    int y = (windowH/2 - textSurface->h/2);
    Entity * fadeInText = new Entity(this->nextId++, x, y, textSurface->w, textSurface->h, textSurface->w, textSurface->h);
    fadeInText->art = new TextFadeInComponent(fadeInText, this->renderer, textSurface, 1, initialAlpha);
    //fadeInText->input = new StartScreenInputComponent(fadeInText);
    return fadeInText;
}

Entity* EntityBuilder::createHorizontallyCenteredFadeInText(FontEnum fontType,
                                                 const char *text, int fontSize,
                                                 int r, int g, int b, int initialAlpha,
                                                 int windowW, int yPos,
                                                 int index, int numOptions, StateEnum nextState) {
    if (!this->fontMap[fontType][fontSize])
        this->loadFont(fontType, fontSize);
    SDL_Surface* textSurface =
        this->createText(fontType, text, fontSize, r, g, b, initialAlpha);
    int x = (windowW/2 - textSurface->w/2);
    Entity* fadeInText = new Entity(this->nextId++, x, yPos, textSurface->w, textSurface->h, textSurface->w, textSurface->h);
    fadeInText->art = new TextFadeInComponent(fadeInText, this->renderer, textSurface, 1, initialAlpha);
    SwitchStateCommand* nextStateCmd = NULL;
    if (nextState != STATE_NONE)
        nextStateCmd = new SwitchStateCommand(nextState);
    fadeInText->input = new MenuOptionInputComponent(fadeInText, index, numOptions, nextStateCmd);
    return fadeInText;
}

Entity* EntityBuilder::createVictoryZone(int x, int y) {        // not using maps, since its a
    Entity* zone = new Entity(this->nextId++, x, y, 50, 50, 50, 50);    // temporary feature
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);
    SDL_Rect tempRect = {0,0,50,50};
    SDL_FillRect(surface, &tempRect, SDL_MapRGB(surface->format, 255, 0, 0));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface);
    zone->art = new StaticArtComponent(zone, texture, 2, false);
    zone->collision = new VictoryZoneCollisionComponent(zone, new SwitchStateCommand(STATE_PLAY));
    return zone;
}

Entity* EntityBuilder::createTerrain(TerrainTexEnum texType, int x, int y, int numberHorizontal,
        bool freeTop, bool freeBot, bool freeRight, bool freeLeft) {
    if (!this->terrainTexMap[texType][numberHorizontal].sdlTexture)
        this->loadTerrain(texType, numberHorizontal);
    Texture texture = this->terrainTexMap[texType][numberHorizontal];
    Entity* terrain = new Entity(this->nextId++, x, y, texture.width, texture.height, texture.width, texture.height);

    terrain->art = new StaticArtComponent(terrain, texture.sdlTexture, 1, false);
    terrain->collision = new TerrainCollisionComponent(terrain, freeTop, freeBot, freeRight, freeLeft);
    return terrain;
}

Entity* EntityBuilder::createProjectile(TextureEnum texType, int x, int y, int dir, int ownerId) {
    Texture texture = this->textureMap[texType];
    Entity* projectile = new Entity(this->nextId++, x, y, texture.width*2, texture.height*2, texture.width*2, texture.height*2);
    projectile->art = new StaticArtComponent(projectile, texture.sdlTexture, 1, false);
    DespawnEntityCommand* dCmd = new DespawnEntityCommand(projectile->getId());
    projectile->collision = new ProjectileCollisionComponent(projectile, dCmd, ownerId);
    projectile->physics = new PhysicsComponent(projectile);
    projectile->physics->xVelocity = dir * 0.6f;
    projectile->physics->yVelocity = -0.4f;
    projectile->physics->deceleration = 0.0f;
    return projectile;
}
