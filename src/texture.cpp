#include <SDL_render.h>
#include "component.h"

Texture::Texture(SDL_Texture *texture, int layer) {
    this->texture = texture;
    this->layer = layer;
};