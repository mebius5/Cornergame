#ifndef CORNERGAME_ENTITY_HANDLER_H
#define CORNERGAME_ENTITY_HANDLER_H

#include <SDL_image.h>
#include <iostream>
#include "entity.h"

class EntityHandler {
public:
    EntityHandler();
    Entity* createHero(SDL_Renderer* renderer, int x, int y);
};

#endif //CORNERGAME_ENTITY_HANDLER_H
