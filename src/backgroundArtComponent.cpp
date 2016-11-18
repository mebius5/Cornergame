#include "artComponent.h"

BackgroundArtComponent::BackgroundArtComponent(Entity* ent, SDL_Texture* tex, float speed) :
    ArtComponent(ent, LAYER_BG, true),
    texture(tex),
    speed(speed) {
}

SDL_Texture* BackgroundArtComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* BackgroundArtComponent::getNextSrcRect(int /*dt*/) {
    return NULL;
}
