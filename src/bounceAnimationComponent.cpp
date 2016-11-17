#include "artComponent.h"

BounceAnimationComponent::BounceAnimationComponent(Entity* entity, Texture tex, int layer):
    AnimationComponent(entity, tex, layer) {
}

SDL_Texture* BounceAnimationComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* BounceAnimationComponent::getNextSrcRect(int dt) {
    if (this->entity->actionState == ACTION_JUMP) {
        this->actionTime += dt;
        clip.x = (actionTime / 125) * 32;
        clip.y = 0;
        if (this->actionTime > 500) {
            this->entity->actionState = ACTION_IDLE;
            this->actionTime = 0;
        }
    } else {
        clip.x = 0;
        clip.y = 32;
    }
    clip.w = (this->surfaceW) / 4;
    clip.h = (this->surfaceH) / 2;
    return &clip;
}

void BounceAnimationComponent::restartAnimation() {
    this->actionTime = 0;
}
