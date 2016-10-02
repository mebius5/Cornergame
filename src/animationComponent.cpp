#include "artComponent.h"
#include <iostream>
#include <math.h>

AnimationComponent::AnimationComponent(SDL_Texture* texture, SDL_Surface* surface, int layer, Entity * entity) :
    texture(texture),
    surface(surface) {
    this->layer = layer;
    timecount = 0;
    clip = {0,0,0,0};
    this->entity = entity;
}

AnimationComponent::~AnimationComponent() {
    SDL_DestroyTexture(this->texture);
}

SDL_Texture* AnimationComponent::getNextTexture(int dt) {
    return this->texture;
}

SDL_Rect* AnimationComponent::getNextSrcRect(int dt) {
    timecount += dt;
    timecount %= 1000;

    // if moving, use a walking animation, else idle
    float velocity = sqrt(pow(this->entity->xVelocity, 2) +
                          pow(this->entity->yVelocity, 2));
    if (velocity > 0.01) {
        // if moving left, start at middle of sheet
        int startpos = 0;
        if (this->entity->xVelocity < 0) {
            startpos = 32 * 4;
        }
        clip.x = (timecount / 250) * 32 + startpos;
        clip.y = 0;
    } else {
        clip.x = 0;
        clip.y = (timecount / 500) * 32;
    }
    clip.w = (this->surface->w) / 8;
    clip.h = (this->surface->h) / 2;
    return &clip;
}
