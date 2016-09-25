#ifndef CORNERGAME_ENTITY_HANDLER_H
#define CORNERGAME_ENTITY_HANDLER_H

#include <SDL_image.h>
#include <iostream>
#include "entity.h"

class EntityHandler {
private:
    int nextId;
    SDL_Renderer* renderer;
    SDL_Surface* loadImage(const char* filename);
public:
    EntityHandler(SDL_Renderer* renderer);
    Entity* createHero(int x, int y);
    Entity* createEnemy(int x, int y);
};

#endif //CORNERGAME_ENTITY_HANDLER_H
