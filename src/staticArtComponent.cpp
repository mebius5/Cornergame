#include "artComponent.h"

StaticArtComponent::StaticArtComponent(Entity* ent, SDL_Texture* tex, int lay,
                                       bool movesWithCamera) :
    ArtComponent(ent, lay, movesWithCamera),
    texture(tex) {
}

SDL_Texture* StaticArtComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* StaticArtComponent::getNextSrcRect(int /*dt*/) {
    return NULL;
}
