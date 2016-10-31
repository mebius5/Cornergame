#include "artComponent.h"

AmmoBarArtComponent::AmmoBarArtComponent(Entity* entity, Entity* hero,
                                         Texture tex, int layer):
    ArtComponent(entity, layer, true),
    hero(hero),
    texture(tex.sdlTexture),
    width(tex.width / 2),
    height(tex.height) {
    this->clip = {0,0,0,0};
}

SDL_Texture * AmmoBarArtComponent::getNextTexture(int) {
    return this->texture;
}

SDL_Rect * AmmoBarArtComponent::getNextSrcRect(int) {
    float ammoDifference = this->hero->ammo->getMaxAmmo() - this->hero->ammo->getAmmo();
    float positionAddition = width*(ammoDifference/this->hero->ammo->getMaxAmmo());
    this->clip = {0+(int)positionAddition, 0, (int) width, height};

    return & this->clip;
}
