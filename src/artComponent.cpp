#include "artComponent.h"

ArtComponent::ArtComponent(SDL_Texture* texture, int layer) {
    this->texture = texture;
    this->layer = layer;
}

ArtComponent::~ArtComponent() {
    SDL_DestroyTexture(this->texture);
}