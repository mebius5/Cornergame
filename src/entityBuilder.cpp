#include "entityBuilder.h"

EntityBuilder::EntityBuilder(SDL_Renderer* renderer) :
    nextId(0),
    renderer(renderer) {
}

Entity* EntityBuilder::createHero(int x, int y, const char* collisionSfxFile) {
    SDL_Surface* image = this->loadImage("spritesheets/hero.png");
    Entity* hero = new Entity(this->nextId++, x, y, (image->w)/4, (image->h)*2);

    Mix_Chunk* chunk = Mix_LoadWAV(collisionSfxFile);
    if (!chunk) {
        std::cerr << "Unable to load chunk: " << Mix_GetError() << std::endl;
        return NULL;
    }

    hero->collision = new CollisionComponent(new PlaySoundCommand(chunk), NULL);
    hero->art = new AnimationComponent(
        SDL_CreateTextureFromSurface(this->renderer, image), image, 1);
    hero->input = new HeroInputComponent(hero);
    return hero;
}

Entity* EntityBuilder::createEnemy(int x, int y) {
    SDL_Surface* image = this->loadImage("spritesheets/lax.png");
    Entity* enemy = new Entity(this->nextId++, x, y, (image->w)/4, (image->h)*2);

    enemy->collision = new CollisionComponent(NULL, new ResetAiCommand(enemy));
    enemy->art = new AnimationComponent(
        SDL_CreateTextureFromSurface(this->renderer, image), image, 1);
    enemy->ai = new AiComponent(enemy);
    return enemy;
}

Entity * EntityBuilder::createBackground(const char * filename, int width, int height) {
    SDL_Surface * image = this->loadImage(filename);
    Entity * background = new Entity(this->nextId++, 0, 0, width, height);
    background->art = new StaticArtComponent(SDL_CreateTextureFromSurface(this->renderer, image),0);
    SDL_FreeSurface(image);
    return background;
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
    fadeInText->input = new StartScreenInputComponent(fadeInText);
    return fadeInText;
}

Entity * EntityBuilder::createHorizontallyCenteredFadeInText(const char *fontName,
                                                 const char *text,
                                                 int fontSize,
                                                 int r, int g, int b, int initialAlpha,
                                                 int windowW, int yPos,
                                                 int index, int numOptions, int nextState) {
    SDL_Surface * textSurface = this->loadFont(fontName, text, fontSize, r, g, b, initialAlpha);
    int x = (windowW/2 - textSurface->w/2);
    Entity * fadeInText = new Entity(this->nextId++, x, yPos, textSurface->w, textSurface->h);
    fadeInText->art = new TextFadeInComponent(this->renderer, textSurface, 1, initialAlpha);
    SwitchStateCommand* nextStateCmd = NULL;
    if (nextState)
        nextStateCmd = new SwitchStateCommand(nextState);
    fadeInText->input = new MenuOptionInputComponent(fadeInText, index, numOptions,
                                                     new SelectMenuOptionCommand(fadeInText),
                                                     new DeselectMenuOptionCommand(fadeInText),
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
