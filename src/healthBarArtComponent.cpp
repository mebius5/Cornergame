#include "artComponent.h"

HealthBarArtComponent::HealthBarArtComponent(Entity* entity, Entity* owner, Texture tex):
    ArtComponent(entity, LAYER_HUD, true),
    texture(tex.sdlTexture),
    ownerHealth(owner->health),
    width(tex.width / 2),
    height(tex.height),
    lastHealth(-1) {
    this->clip = {0,0,0,0};
}

SDL_Texture * HealthBarArtComponent::getNextTexture(int) {
    return this->texture;
}

SDL_Rect * HealthBarArtComponent::getNextSrcRect(int) {
    //entity->x = ownerHealth->entity->x;
    //entity->y = ownerHealth->entity->y-(2*this->height);

    if (this->lastHealth!=this->ownerHealth->getHealth()) {
        this->lastHealth = this->ownerHealth->getHealth();
        float healthDifference = this->ownerHealth->getMaxHealth() - this->lastHealth;
        float positionAddition = width*(healthDifference/this->ownerHealth->getMaxHealth());
        this->clip = {0+(int)positionAddition, 0, (int) width, height};
    }

    return & this->clip;
}
