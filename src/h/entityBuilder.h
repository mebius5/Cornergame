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
    SDL_Surface* loadImage(const char* filename);
public:
    EntityBuilder(SDL_Renderer* renderer);
    Entity* createHero(int x, int y, const char* collisionSfxFile);
    Entity* createEnemy(int x, int y);
};

#endif
