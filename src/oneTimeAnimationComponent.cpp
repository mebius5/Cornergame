#include "artComponent.h"

OneTimeAnimationComponent::OneTimeAnimationComponent(Entity* entity, Texture animationTex,
                                                     LayerEnum layer, int animationTime,
                                                     int frames, Texture defaultTex) :
    AnimationComponent(entity, defaultTex, layer),
    despawnCommand(new DespawnEntityCommand(entity->getId())),
    animationTime(animationTime),
    frames(frames),
    animationTex(animationTex),
    started(false) {
}

void OneTimeAnimationComponent::startAnimation() {
    if (this->started)
        return;
    this->started = true;

    this->entity->drawWidth = animationTex.width / this->frames;
    this->entity->drawHeight = animationTex.height;
    this->texture = animationTex.sdlTexture;
    this->surfaceW = animationTex.width;
    this->surfaceH = animationTex.height;
}

OneTimeAnimationComponent::~OneTimeAnimationComponent() {
    delete this->despawnCommand;
}

SDL_Rect* OneTimeAnimationComponent::getNextSrcRect(int dt) {
    if (!this->started)     // return full source rect before activated
        return NULL;

    this->actionTime += dt;
    clip.x = (this->actionTime / (this->animationTime/this->frames)) * this->surfaceW;
    clip.y = 0;
    clip.w = (this->surfaceW) / this->frames;
    clip.h = this->surfaceH;
    if (this->actionTime >= this->animationTime)
        Component::commandList->push_back(this->despawnCommand);
    return &clip;
}
