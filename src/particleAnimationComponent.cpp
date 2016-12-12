#include "artComponent.h"

ParticleAnimationComponent::ParticleAnimationComponent(Entity* entity, Texture tex):
    AnimationComponent(entity, tex, LAYER_OVERLAY),
    despawnCommand(new DespawnEntityCommand(entity->getId())),
    counter(0),
    lastDraw(0) {
}

ParticleAnimationComponent::~ParticleAnimationComponent() {
    delete this->despawnCommand;
}

void ParticleAnimationComponent::updateLocation() {
    if (counter - lastDraw > 5)
        Component::commandList->push_back(this->despawnCommand);
    counter++;
}

SDL_Texture* ParticleAnimationComponent::getNextTexture(int /*dt*/) {
    lastDraw = counter;
    return this->texture;
}

SDL_Rect* ParticleAnimationComponent::getNextSrcRect(int dt) {
    this->actionTime += dt;
    clip.x = (actionTime / 125) * 8;
    clip.y = 0;
    clip.w = this->surfaceW / 4;
    clip.h = this->surfaceH;
    if (this->actionTime >= 500) {
        Component::commandList->push_back(this->despawnCommand);
    }
    return &clip;
}
