#include "artComponent.h"

StaticArtComponent::StaticArtComponent(Entity* ent, SDL_Texture* tex,
                                       LayerEnum layer, bool movesWithCamera) :
    ArtComponent(ent, layer, movesWithCamera),
    texture(tex),
    lightTexture(NULL)
{
}

SDL_Texture* StaticArtComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* StaticArtComponent::getNextSrcRect(int /*dt*/) {
    return NULL;
}