#include "artComponent.h"

HealthBarArtComponent::HealthBarArtComponent(Entity* entity, Texture tex,
                                             Entity *owner, int layer):
    ArtComponent(entity, layer, true),
    texture(tex.sdlTexture),
    owner(owner),
    width(tex.width / 2),
    height(tex.height),
    lastHealth(-1)
{
    this->clip = {0,0,0,0};
}

SDL_Texture * HealthBarArtComponent::getNextTexture(int) {
    return this->texture;
}

SDL_Rect * HealthBarArtComponent::getNextSrcRect(int) {

    if(this->lastHealth!=this->owner->health->getHealth()) {
        this->lastHealth = this->owner->health->getHealth();
        float healthDifference = this->owner->health->getMaxHealth() - this->lastHealth;
        float positionAddition = width*(healthDifference/this->owner->health->getMaxHealth());
        this->clip = {0+(int)positionAddition, 0, (int) width, height};
    }

    return & this->clip;
}
