#include "artComponent.h"

HealthBarArtComponent::HealthBarArtComponent(SDL_Texture *texture,
                                             Entity *owner, int layer, float width, int height):
    ArtComponent(owner, layer),
    texture(texture),
    width(width),
    height(height),
    lastHealth(-1)
{
    this->clip = {0,0,0,0};
}

HealthBarArtComponent::~HealthBarArtComponent() {
    this->entity = NULL;
    if(this->texture){
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
}

SDL_Texture * HealthBarArtComponent::getNextTexture(int) {
    return this->texture;
}

SDL_Rect * HealthBarArtComponent::getNextSrcRect(int) {

    if(this->lastHealth!=this->entity->health->getHealth()) {
        this->lastHealth = this->entity->health->getHealth();
        float healthDifference = this->entity->health->getMaxHealth() - this->lastHealth;
        float positionAddition = width*(healthDifference/this->entity->health->getMaxHealth());
        this->clip = {0+(int)positionAddition, 0, (int) width, height};
    }

    return & this->clip;
}