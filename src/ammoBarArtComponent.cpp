#include "artComponent.h"

AmmoBarArtComponent::AmmoBarArtComponent(Entity* entity, Entity* owner, Texture tex, int layer):
    ArtComponent(entity, layer, false),
    texture(tex.sdlTexture),
    ownerAmmo(owner->ammo),
    width(tex.width / 2),
    height(tex.height) {
    this->clip = {0,0,0,0};
}

void AmmoBarArtComponent::updateLocation() {
    this->entity->x = ownerAmmo->entity->x+(ownerAmmo->entity->width)/2-(this->width/2);
    this->entity->y = ownerAmmo->entity->y-this->height;
}

SDL_Texture* AmmoBarArtComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* AmmoBarArtComponent::getNextSrcRect(int /*dt*/) {
    float ammoDifference = ownerAmmo->getMaxAmmo() - ownerAmmo->getAmmo();
    float positionAddition = width*(ammoDifference/ownerAmmo->getMaxAmmo());
    this->clip = {(int)positionAddition, 0, (int)width, height};
    return &this->clip;
}
