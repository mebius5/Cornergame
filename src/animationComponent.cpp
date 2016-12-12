#include "artComponent.h"

AnimationComponent::AnimationComponent(Entity* entity, Texture tex, LayerEnum layer):
    ArtComponent(entity, layer, false),
    texture(tex.sdlTexture),
    surfaceW(tex.width),
    surfaceH(tex.height),
    timecount(0),
    collisionComp(static_cast<DynamicCollisionComponent*>(entity->collision)) {
    this->clip = {0,0,0,0};
    this->actionTime = 0;
}

SDL_Texture* AnimationComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* AnimationComponent::getNextSrcRect(int dt) {
    bool& onGround = this->collisionComp->onGround;
    bool& onLeftWall = this->collisionComp->onLeftWall;
    bool& onRightWall = this->collisionComp->onRightWall;
    if ((onLeftWall && this->entity->dir == -1)
            || (onRightWall && this->entity->dir == 1)) {
        this->entity->actionState = ACTION_SLIDING;
    }
    int startpos = 0;
    if (this->entity->dir == -1) {
        startpos = 128;
    }
    if (this->entity->actionState == ACTION_IDLE) {
        timecount += dt;
        timecount %= 500;

        // if moving, use a walking animation, else idle
        float sqnorm = (float) (pow(this->entity->physics->xVelocity, 2)
                                + pow(this->entity->physics->yVelocity, 2));
        if (sqnorm > 0.0001) {
            clip.x = (timecount / 125) * 32 + startpos;
            clip.y = 0;
        } else {
            clip.x = (timecount / 250) * 32 + startpos;
            clip.y = 32;
        }
    } else if (this->entity->actionState == ACTION_THROW) {
        this->actionTime += dt;
        if (this->actionTime > 240) {
            this->actionTime = 0;
            this->entity->actionState = ACTION_IDLE;
        }
        clip.x = (actionTime / 60) * 32 + startpos;
        clip.y = 64;

    } else if (this->entity->actionState == ACTION_JUMP) {
        this->actionTime += dt;
        clip.x = (actionTime / 100) * 32 + startpos;
        clip.y = 96;
        if (this->actionTime > 400) {
            clip.x = 96 + startpos;
        }
        if (onGround) {
            this->entity->actionState = ACTION_IDLE;
            this->actionTime = 0;
        }
    } else if (this->entity->actionState == ACTION_DODGE) {
        this->actionTime += dt;
        if (this->actionTime > 360) {
            this->actionTime = 0;
            this->entity->actionState = ACTION_IDLE;
        }
        clip.x = (actionTime / 90) * 32 + startpos;
        clip.y = 160;
    } else if (this->entity->actionState == ACTION_SLIDING) {
        this->actionTime += dt;
        clip.x = (actionTime / 250) * 32 + startpos;
        clip.y = 128;
        this->actionTime %= 1000;
        if (onGround || (!onLeftWall && !onRightWall)) {
            this->entity->actionState = ACTION_IDLE;
            this->actionTime = 0;
        }
    } else if (this->entity->actionState == ACTION_DAMAGE) {
        this->entity->health->setIsInvincible(true);
        this->actionTime += dt;
        if (this->actionTime > 1000) {
            this->actionTime = 0;
            this->entity->actionState = ACTION_IDLE;
            this->entity->health->setIsInvincible(false);
        }
        clip.x = ((actionTime / 250) % 2) * 32 + startpos + 32;
        clip.y = 32;
    }
    clip.w = (this->surfaceW) / 8;
    clip.h = (this->surfaceH) / 6;
    return &clip;
}

double AnimationComponent::getNextAngle(int /*dt*/) {
    if (this->entity->rotates && this->entity->actionState == ACTION_DODGE) {
        return this->actionTime * entity->dir;
    } else {
        return 0;
    }
}

SDL_RendererFlip AnimationComponent::getNextFlip(int /*dt*/) {
    return SDL_FLIP_NONE;
}
