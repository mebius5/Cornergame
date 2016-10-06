#include "entityBuilder.h"

EntityBuilder::EntityBuilder(SDL_Renderer* renderer) :
    nextId(0),
    renderer(renderer) {
}

Entity* EntityBuilder::createHero(int x, int y, const char* collisionSfxFile) {
    SDL_Surface* image = this->loadImage("spritesheets/hero.png");
    Entity* hero = new Entity(this->nextId++, x, y, (image->w)/4, (image->h));

    if (collisionSfxFile) {
        Mix_Chunk* chunk = Mix_LoadWAV(collisionSfxFile);
        if (!chunk) {
            std::cerr << "Failed to load chunk: " << Mix_GetError() << std::endl;
            return NULL;
        }
        hero->collision = new HeroCollisionComponent(new PlaySoundCommand(chunk), hero);
    } else
        hero->collision = new HeroCollisionComponent(NULL, hero);

    hero->art = new AnimationComponent(
        SDL_CreateTextureFromSurface(this->renderer, image), image->w, image->h, 1, hero);
    SDL_FreeSurface(image);
    hero->input = new HeroInputComponent(hero);
    hero->score = new ScoreComponent(hero);
    hero->health = new HealthComponent(hero, 300);
    return hero;
}

Entity* EntityBuilder::createEnemy(int x, int y) {
    SDL_Surface* image = this->loadImage("spritesheets/lax.png");
    Entity* enemy = new Entity(this->nextId++, x, y, (image->w)/4, (image->h));

    enemy->collision = new EnemyCollisionComponent(enemy, new ResetAiCommand());
    enemy->art = new AnimationComponent(
        SDL_CreateTextureFromSurface(this->renderer, image), image->w, image->h, 1, enemy);
    SDL_FreeSurface(image);
    enemy->ai = new EnemyAiComponent(enemy);
    enemy->health = new HealthComponent(enemy, 200);
    return enemy;
}

Entity * EntityBuilder::createBackground(const char * filename, int width, int height) {
    SDL_Surface * image = this->loadImage(filename);
    Entity * background = new Entity(this->nextId++, 0, 0, width, height);
    background->art = new StaticArtComponent(SDL_CreateTextureFromSurface(this->renderer, image),0);
    SDL_FreeSurface(image);
    return background;
}

Entity * EntityBuilder::createHealthBar(int x, int y, int width, int height, Entity * owner){
    Entity * healthBar = new Entity(this->nextId++, x, y, width, height);

    SDL_Surface * tempSurface = SDL_CreateRGBSurface(0, width*2, height, 32, 0, 0, 0, 0);
    SDL_Rect tempRect = {0,0,width,height};
    SDL_FillRect(tempSurface, &tempRect, SDL_MapRGB(tempSurface->format, 0, 255, 0));
    tempRect = {width,0, width, height};
    SDL_FillRect(tempSurface, &tempRect, SDL_MapRGB(tempSurface->format, 255, 0, 0));

    SDL_Texture * texture = SDL_CreateTextureFromSurface(this->renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    healthBar->art = new HealthBarArtComponent(texture, owner, 2, width, height);

    return healthBar;
}

Entity * EntityBuilder::createCenteredFadeInText(const char *fontName,
                                                 const char *text,
                                                 int fontSize,
                                                 int r, int g, int b, int initialAlpha,
                                                 int windowW, int windowH) {
    SDL_Surface * textSurface = this->loadFont(fontName, text, fontSize, r, g, b, initialAlpha);
    int x = (windowW/2 - textSurface->w/2);
    int y = (windowH/2 - textSurface->h/2);
    Entity * fadeInText = new Entity(this->nextId++, x, y, textSurface->w, textSurface->h);
    fadeInText->art = new TextFadeInComponent(this->renderer, textSurface, 1, initialAlpha);
    //fadeInText->input = new StartScreenInputComponent(fadeInText);
    return fadeInText;
}

Entity * EntityBuilder::createHorizontallyCenteredFadeInText(const char *fontName,
                                                 const char *text,
                                                 int fontSize,
                                                 int r, int g, int b, int initialAlpha,
                                                 int windowW, int yPos,
                                                 int index, int numOptions, StateEnum nextState) {
    SDL_Surface * textSurface = this->loadFont(fontName, text, fontSize, r, g, b, initialAlpha);
    int x = (windowW/2 - textSurface->w/2);
    Entity * fadeInText = new Entity(this->nextId++, x, yPos, textSurface->w, textSurface->h);
    fadeInText->art = new TextFadeInComponent(this->renderer, textSurface, 1, initialAlpha);
    SwitchStateCommand* nextStateCmd = NULL;
    if (nextState)
        nextStateCmd = new SwitchStateCommand(nextState);
    fadeInText->input = new MenuOptionInputComponent(fadeInText, index, numOptions,
                                                     new SelectMenuOptionCommand(),
                                                     new DeselectMenuOptionCommand(),
                                                     nextStateCmd);
    return fadeInText;
}

SDL_Surface* EntityBuilder::loadFont(const char * fontName,
                      const char * text,
                      int fontSize,
                      int r, int g, int b, int initialAlpha){
    TTF_Font * font = TTF_OpenFont(fontName, fontSize);
    SDL_Color color={(Uint8)r,(Uint8) g,(Uint8) b, 255};
    SDL_Surface* textSurf = TTF_RenderUTF8_Blended(font, text, color);
    TTF_CloseFont(font);
    if (textSurf == NULL) {
        std::cerr << "Unable to load text surface! SDL_image Error: "
                  << IMG_GetError() << std::endl;
        return NULL;
    }
    if(textSurf){
        SDL_SetSurfaceAlphaMod(textSurf, initialAlpha);
    }
    return textSurf;
}

// Surface must be freed when done!
SDL_Surface* EntityBuilder::loadImage(const char* filename) {
    SDL_Surface* image = IMG_Load(filename);
    if (image == NULL) {
        std::cerr << "Unable to load image! SDL_image Error: "
                  << IMG_GetError() << std::endl;
        return NULL;
    }

    SDL_Surface* finalImage = SDL_ConvertSurface(image, image->format, 0);
    SDL_FreeSurface(image);
    if (finalImage == NULL) {
        std::cerr << "Unable to optimize image! SDL Error: "
                  << SDL_GetError() << std::endl;
        return NULL;
    }
    return finalImage;
}
