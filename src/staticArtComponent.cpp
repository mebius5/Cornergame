#include "artComponent.h"

StaticArtComponent::StaticArtComponent(SDL_Texture* texture, int layer) :
    texture(texture) {
    this->layer = layer;
}

StaticArtComponent::~StaticArtComponent() {
    SDL_DestroyTexture(this->texture);
}

SDL_Texture* StaticArtComponent::getNextTexture(int dt) {
    return this->texture;
}
