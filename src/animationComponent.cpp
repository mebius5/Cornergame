#include "artComponent.h"

AnimationComponent::AnimationComponent(Entity* entity, SDL_Texture* texture,
                                       int surfaceW, int surfaceH, int layer):
    ArtComponent(entity, layer, false),
    texture(texture),
    surfaceW(surfaceW),
    surfaceH(surfaceH),
    timecount(0) {
    this->clip = {0,0,0,0};
    this->actionTime = 0;   
}

AnimationComponent::~AnimationComponent() {
    if(this->texture){
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
    this->entity = NULL;
}

SDL_Texture* AnimationComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* AnimationComponent::getNextSrcRect(int dt) {
    if (this->entity->actionState == IDLE) {

        timecount += dt;
        timecount %= 1000;

        // if moving, use a walking animation, else idle
        float velocity = sqrt(pow(this->entity->xVelocity, 2) +
                              pow(this->entity->yVelocity, 2));
        if (velocity > 0.03) {
            // if moving left, start at middle of sheet
            int startpos = 0;
            if (this->entity->xVelocity < 0) {
                startpos = 32 * 4;
            }
            clip.x = (timecount / 250) * 32 + startpos;
            clip.y = 0;
        } else {
            clip.x = (timecount / 500) * 32;
            clip.y = 32;
        }
        clip.w = (this->surfaceW) / 8;
        clip.h = (this->surfaceH) / 4;
    } else {
        this->actionTime += dt;
        if (this->actionTime > 1000) {
            this->actionTime = 0;
            this->entity->actionState = IDLE;
        }
        clip.x = (actionTime / 250) * 32;
        clip.y = 64;
        clip.w = (this->surfaceW) / 8;
        clip.h = (this->surfaceH) / 4;

    }
    return &clip;
}
