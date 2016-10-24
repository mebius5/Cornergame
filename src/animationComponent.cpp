#include "artComponent.h"

AnimationComponent::AnimationComponent(Entity* entity, Texture tex, int layer):
    ArtComponent(entity, layer, false),
    texture(tex.sdlTexture),
    surfaceW(tex.width),
    surfaceH(tex.height),
    collisionComp(static_cast<DynamicCollisionComponent*>(entity->collision)),
    timecount(0) {
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
    if (onLeftWall || onRightWall) {
        this->entity->actionState = SLIDING;
    }
    int startpos = 0;
    if (this->entity->dir == -1) {
        startpos = 128;
    }
    if (this->entity->actionState == IDLE) {

        timecount += dt;
        timecount %= 1000;

        // if moving, use a walking animation, else idle
        float velocity = sqrt(pow(this->entity->physics->xVelocity, 2) +
                              pow(this->entity->physics->yVelocity, 2));
        startpos = 0;
        if (this->entity->physics->xVelocity < 0) {
            startpos = 32 * 4;
        }
        if (velocity > 0.01) {
            clip.x = (timecount / 250) * 32 + startpos;
            clip.y = 0;
        } else {
            clip.x = (timecount / 500) * 32 + startpos;
            clip.y = 32;
        }
        clip.w = (this->surfaceW) / 8;
        clip.h = 32;
    } else if (this->entity->actionState == THROW) {
        this->actionTime += dt;
        if (this->actionTime > 1000) {
            this->actionTime = 0;
            this->entity->actionState = IDLE;
        }
        clip.x = (actionTime / 250) * 32 + startpos;
        clip.y = 64;
        clip.w = (this->surfaceW) / 8;
        clip.h = 32;

    } else if (this->entity->actionState == JUMP) {
        this->actionTime += dt;
        clip.x = (actionTime / 250) * 32 + startpos;
        clip.y = 96;
        clip.w = (this->surfaceW) / 8;
        clip.h = 32;
        if (this->actionTime > 1000) {
            clip.x = 96 + startpos;
        }
        if (onGround) {
            this->entity->actionState = IDLE;
            this->actionTime = 0;
        }
    } else if (this->entity->actionState == SLIDING) {
        this->actionTime += dt;
        clip.x = (actionTime / 250) * 32 + startpos;
        clip.y = 128;
        clip.w = (this->surfaceW) / 8;
        clip.h = 32;
        this->actionTime %= 1000;
        if (onGround) {
            this->entity->actionState = IDLE;
            this->actionTime = 0;
        }
    } else if (this->entity->actionState == DAMAGE) {
        this->actionTime += dt;
        if (this->actionTime > 1000) {
            this->actionTime = 0;
            this->entity->actionState = IDLE;
        }
        clip.x = ((actionTime / 250)%2) * 32 + startpos + 32;
        clip.y = 32;
        clip.w = (this->surfaceW) / 8;
        clip.h = 32;

    }
    return &clip;
}
