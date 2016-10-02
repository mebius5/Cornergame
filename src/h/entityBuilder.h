#ifndef CORNERGAME_ENTITY_BUILDER_H
#define CORNERGAME_ENTITY_BUILDER_H

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "entity.h"

class EntityBuilder {
private:
    int nextId;
    SDL_Renderer* renderer;
    SDL_Surface * loadImage(const char * filename);
    SDL_Surface* loadFont(const char * fontName,
                          const char * text,
                          int fontSize,
                          int r, int g, int b, int initialAlpha);
public:
    EntityBuilder(SDL_Renderer* renderer);
    Entity* createHero(int x, int y, const char* collisionSfxFile);
    Entity* createEnemy(int x, int y);
    Entity* createBackground(const char * filename, int width, int height);
    Entity * createFadeInText(const char * fontName,
                              const char * text,
                              int fontSize,
                              int r, int g, int b, int initialAlpha,
                              int windowW, int windowH);
};

#endif
