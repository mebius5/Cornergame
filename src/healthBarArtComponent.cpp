#include "artComponent.h"

HealthBarArtComponent::HealthBarArtComponent(SDL_Texture *texture,
                                             Entity *owner, int layer, float width, int height):
    ArtComponent(owner, layer),
    texture(texture),
    width(width),
    height(height)
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

SDL_Rect * HealthBarArtComponent::getNextSrcRect(int dt) {

    float healthDifference = 100 - dt; //TODO: Need to get replace with hero health from entity health component

    float positionAddition = width*(healthDifference/100);

    this->clip = {0+(int)positionAddition, 0, (int) width, height};

    return & this->clip;
}