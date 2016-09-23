
#include <SDL_render.h>
#include "entity.h"

Hero::Hero(int startX, int startY, int width, int height) {
    this->location = new Location(startX, startY, width, height);
}

