#include "artComponent.h"

PowerUpArtComponent::PowerUpArtComponent(Entity* entity, Entity * owner, Texture tex, int layer, int index):
    ArtComponent(entity, layer, false),
    texture(tex.sdlTexture),
    powerUp(owner->powerUp),
    index(index) {
    this->clip = {0,0,32,32};
    this->timecount = 0;
}

void PowerUpArtComponent::updateLocation() {
    entity->x = powerUp->entity->x;
    entity->y = powerUp->entity->y;
}

SDL_Texture* PowerUpArtComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* PowerUpArtComponent::getNextSrcRect(int dt) {
    if (powerUp->pwrUPTimerArray[index]!=-999) {
        timecount += dt;
        timecount %= 500;
        clip.x = (timecount / 125) * 32;
        clip.y = 0;
    } else {
        clip.y = 32;
    }
    return &clip;
}
