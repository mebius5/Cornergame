#include "artComponent.h"

ParticleAnimationComponent::ParticleAnimationComponent(Entity* entity, Texture tex):
    AnimationComponent(entity, tex, LAYER_OVERLAY) {
}

SDL_Texture* ParticleAnimationComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* ParticleAnimationComponent::getNextSrcRect(int dt) {
    this->actionTime += dt;
    clip.x = (actionTime / 125) * 8;
    clip.y = 0;
    clip.w = this->surfaceW / 4;
    clip.h = this->surfaceH;
    return &clip;
}
