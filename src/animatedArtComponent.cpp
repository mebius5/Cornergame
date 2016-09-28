#include <SDL_render.h>
#include "artComponent.h"

AnimatedArtComponent::AnimatedArtComponent(SDL_Texture *texture, int layer) {
    this->texture = texture;
    this->layer = layer;
}

AnimatedArtComponent::~AnimatedArtComponent() {
    SDL_DestroyTexture(this->texture);
}

SDL_Texture * AnimatedArtComponent::getNextTexture(int dTime) {
    return this->texture;
}