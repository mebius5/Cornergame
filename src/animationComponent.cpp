#include "artComponent.h"

AnimationComponent::AnimationComponent(SDL_Texture* texture, SDL_Surface* surface, int layer) :
    texture(texture),
    surface(surface) {
    this->layer = layer;
    timecount = 0;
    clip = {0,0,0,0};
}

AnimationComponent::~AnimationComponent() {
    SDL_DestroyTexture(this->texture);
}

SDL_Texture* AnimationComponent::getNextTexture(int dt) {
    return this->texture;
}

SDL_Rect* AnimationComponent::getNextSrcRect(int dt) {
    clip.x = 0;
    clip.y = 0;
    clip.w = 32;
    clip.h = 32;
    return &clip;
}
