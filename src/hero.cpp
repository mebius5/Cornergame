
#include <SDL_render.h>
#include "entity.h"

Hero::Hero(int startX, int startY, SDL_Texture * texture) {
    this->location = new Location(startX, startY);
}

