#include "artComponent.h"
#include<iostream>

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
    // if moving left, start at middle of sheet
    int startpos = 0;
    if (this->entity->xVelocity < 0) {
        startpos = 32 * 4;
    }
    timecount += dt;
    timecount %= 1000;
    clip.x = (timecount / 250)*32 + startpos;
    clip.y = 0;
    clip.w = (this->surface->w)/8;
    clip.h = (this->surface->h);
    return &clip;
}
