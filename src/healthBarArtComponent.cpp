#include "artComponent.h"

HealthBarArtComponent::HealthBarArtComponent(Entity* entity, SDL_Texture *texture,
                                             Entity *owner, int layer, float width, int height):
    ArtComponent(entity, layer),
    texture(texture),
    owner(owner),
    width(width),
    height(height),
    lastHealth(-1)
{
    this->clip = {0,0,0,0};
}

HealthBarArtComponent::~HealthBarArtComponent() {
    this->entity = NULL;
    this->owner = NULL;
    if(this->texture){
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
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
