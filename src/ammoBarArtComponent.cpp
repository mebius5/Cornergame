#include "artComponent.h"

AmmoBarArtComponent::AmmoBarArtComponent(Entity *entity, Entity *owner, Texture tex, int layer):
        OverlayArtComponent(entity,tex,layer),
        ownerAmmo(owner->ammo),
        width(tex.width / 2),
        height(tex.height)
{
    this->clip = {0,0,0,0};

}

SDL_Texture * AmmoBarArtComponent::getNextTexture(int) {
    return this->texture;
}

SDL_Rect * AmmoBarArtComponent::getNextSrcRect(int) {
    entity->x = ownerAmmo->entity->x;
    entity->y = ownerAmmo->entity->y-this->height;

    float ammoDifference = ownerAmmo->getMaxAmmo() - ownerAmmo->getAmmo();
    float positionAddition = width*(ammoDifference/ownerAmmo->getMaxAmmo());
    this->clip = {0+(int)positionAddition, 0, (int) width, height};

    return & this->clip;
}
