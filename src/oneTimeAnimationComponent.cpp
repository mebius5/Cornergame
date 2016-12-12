#include "artComponent.h"

OneTimeAnimationComponent::OneTimeAnimationComponent(Entity* entity, Texture animationTex,
                                                     LayerEnum layer, int animationTime) :
    AnimationComponent(entity, animationTex, layer),
    despawnCommand(new DespawnEntityCommand(entity->getId())),
    animationTime(animationTime),
    animationTex(animationTex),
    started(false),
    ended(false) {
}

void OneTimeAnimationComponent::startAnimation() {
    if (this->started)
        return;
    this->started = true;
    this->actionTime = 0;
    this->entity->drawWidth *= 3;
    this->entity->drawHeight *= 3;
    this->surfaceW = animationTex.width;
    this->surfaceH = animationTex.height;
}

OneTimeAnimationComponent::~OneTimeAnimationComponent() {
    delete this->despawnCommand;
}

SDL_Rect* OneTimeAnimationComponent::getNextSrcRect(int dt) {
    if (!this->started) {
        this->actionTime += dt;
        this->actionTime %= 400;
        clip.x = (this->actionTime / 50) * 32;
        clip.y = 0;
        clip.w = 32;
        clip.h = 32;
    } else {
        this->actionTime += dt;
        if (this->actionTime < 500) {
            clip.x = (this->actionTime / 75) * 32;
        } else if (!this->ended) {
            this->ended = true;;
            this->entity->height /= 3;
            clip.x = 224;
        } else {
            clip.x = 224;
        }
        clip.y = 32;
        clip.w = 32;
        clip.h = 32;
        if (this->actionTime >= this->animationTime)
            Component::commandList->push_back(this->despawnCommand);
    }

    return &clip;
}



