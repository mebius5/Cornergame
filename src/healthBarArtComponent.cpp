#include "artComponent.h"

HealthBarArtComponent::HealthBarArtComponent(Entity* entity, Texture tex,
                                             HealthComponent *ownerHealth, int layer):
    ArtComponent(entity, layer, true),
    texture(tex.sdlTexture),
    ownerHealth(ownerHealth),
    width(tex.width / 2),
    height(tex.height),
    lastHealth(-1) {
    this->clip = {0,0,0,0};
}

SDL_Texture * HealthBarArtComponent::getNextTexture(int) {
    return this->texture;
}

SDL_Rect * HealthBarArtComponent::getNextSrcRect(int) {
    if (this->lastHealth!=this->ownerHealth->getHealth()) {
        this->lastHealth = this->ownerHealth->getHealth();
        float healthDifference = this->ownerHealth->getMaxHealth() - this->lastHealth;
        float positionAddition = width*(healthDifference/this->ownerHealth->getMaxHealth());
        this->clip = {0+(int)positionAddition, 0, (int) width, height};
    }

    return & this->clip;
}
