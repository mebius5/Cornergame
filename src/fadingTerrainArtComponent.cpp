#include "artComponent.h"

FadingTerrainArtComponent::FadingTerrainArtComponent(Entity *entity, SDL_Texture *texture):
    ArtComponent(entity, LAYER_TERRAIN1, false),
    texture(texture),
    shakeTime(-999),
    maxShakeTime(1000) {
    this->clip = {0,0,32,32};
}

void FadingTerrainArtComponent::startShake() {
    this->shakeTime=maxShakeTime;
}

SDL_Texture* FadingTerrainArtComponent::getNextTexture(int) {
    return this->texture;
}

SDL_Rect* FadingTerrainArtComponent::getNextSrcRect(int dt) {
    clip.x = 0;
    if (shakeTime != -999) {
        this->shakeTime -= dt;
        if (this->shakeTime > 0) {
            clip.x = (1000 - shakeTime)/100 * 32;
        } else {
            this->shakeTime = -999;
            this->isVisible = false;
            if(FadingTerrainColComponent * ft = dynamic_cast<FadingTerrainColComponent *>(this->entity->collision)){
                ft->setHasDisappeared(true);
            }
        }
    }
    return &clip;
}

void FadingTerrainArtComponent::resetComponent() {
    this->shakeTime=-999;
    this->isVisible=true;
}