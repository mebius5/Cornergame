#include "artComponent.h"

StaticArtComponent::StaticArtComponent(SDL_Texture* texture, int layer) :
    texture(texture) {
    this->layer = layer;
}

StaticArtComponent::~StaticArtComponent() {
    if(this->texture){
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
}

SDL_Texture* StaticArtComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* StaticArtComponent::getNextSrcRect(int /*dt*/) {
    return NULL;
}
