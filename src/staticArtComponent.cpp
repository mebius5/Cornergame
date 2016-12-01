#include "artComponent.h"

StaticArtComponent::StaticArtComponent(Entity* ent, SDL_Texture* tex,
                                       LayerEnum layer, bool movesWithCamera) :
    ArtComponent(ent, layer, movesWithCamera),
    texture(tex),
    lightTexture(NULL)
{
}

StaticArtComponent::StaticArtComponent(Entity *entity, SDL_Texture *texture, Texture * lightTexture, LayerEnum layer,
                                       bool movesWithCamera):
    StaticArtComponent(entity,texture,layer,movesWithCamera)
{
    this->lightTexture=lightTexture;
    SDL_SetTextureBlendMode(lightTexture->sdlTexture,SDL_BLENDMODE_ADD);
}

SDL_Texture* StaticArtComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* StaticArtComponent::getNextSrcRect(int /*dt*/) {
    return NULL;
}

Texture * StaticArtComponent::getLightTexture() {
    return this->lightTexture;
}