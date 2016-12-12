#include "artComponent.h"

BombIndicatorArtComponent::BombIndicatorArtComponent(Entity* entity, Entity* owner, Texture tex):
    ArtComponent(entity, LAYER_HUD, false),
    texture(tex.sdlTexture),
    ownerAmmo(owner->ammo),
    width(tex.width/8),
    height(tex.height/2) {
    this->clip = {0, 0, tex.width/8, tex.height/2};
}

void BombIndicatorArtComponent::updateLocation() {
    this->isVisible = ownerAmmo->hasBomb;
    this->entity->x = ownerAmmo->entity->x + ownerAmmo->entity->width;
    this->entity->y = ownerAmmo->entity->y - this->height*5/8;
}

SDL_Texture* BombIndicatorArtComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* BombIndicatorArtComponent::getNextSrcRect(int /*dt*/) {
    return &this->clip;
}
