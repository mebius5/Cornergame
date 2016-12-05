#include "artComponent.h"

OneTimeAnimationComponent::OneTimeAnimationComponent(Entity* entity, Texture texture,
                                                     LayerEnum layer, int animationTime,
                                                     int frames) :
    AnimationComponent(entity, texture, layer),
    despawnCommand(new DespawnEntityCommand(entity->getId())),
    animationTime(animationTime),
    frames(frames) {
}

OneTimeAnimationComponent::~OneTimeAnimationComponent() {
    delete this->despawnCommand;
}

SDL_Rect* OneTimeAnimationComponent::getNextSrcRect(int dt) {
    this->actionTime += dt;
    clip.x = (this->actionTime / (this->animationTime/this->frames)) * this->surfaceW;
    clip.y = 0;
    clip.w = (this->surfaceW) / this->frames;
    clip.h = this->surfaceH;
    if (this->actionTime >= this->animationTime)
        Component::commandList->push_back(this->despawnCommand);
    return &clip;
}
