#include <SDL_render.h>
#include "artComponent.h"

StaticArtComponent::StaticArtComponent(SDL_Texture *texture, int layer) {
    this->texture = texture;
    this->layer = layer;
}

StaticArtComponent::~StaticArtComponent() {
    SDL_DestroyTexture(this->texture);
}

SDL_Texture * StaticArtComponent::getNextTexture(int dTime) {
    return this->texture;
}