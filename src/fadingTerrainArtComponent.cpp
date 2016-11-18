#include "artComponent.h"

FadingTerrainArtComponent::FadingTerrainArtComponent(Entity *entity, SDL_Texture *texture):
    ArtComponent(entity, LAYER_TERRAIN, false),
    texture(texture),
    shakeTime(-999),
    maxShakeTime(1000) {
}

void FadingTerrainArtComponent::startShake() {
    this->shakeTime=maxShakeTime;
}

SDL_Texture* FadingTerrainArtComponent::getNextTexture(int dt) {
    int shakeDist = 10;
    if(shakeTime!=-999){
        this->shakeTime -= dt;
        if (this->shakeTime > 0) {
            this->entity->x += (int) (cos(this->shakeTime) * shakeDist * (((float) this->shakeTime) / this->maxShakeTime));
        } else {
            this->shakeTime = -999;
            this->isVisible = false;
            if(FadingTerrainColComponent * ft = dynamic_cast<FadingTerrainColComponent *>(this->entity->collision)){
                ft->setHasDisappeared(true);
            }
        }
    }
    return this->texture;
}

SDL_Rect* FadingTerrainArtComponent::getNextSrcRect(int) {
    return NULL;
}
