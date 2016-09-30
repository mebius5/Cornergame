#include "artComponent.h"

AnimationComponent::AnimationComponent(SDL_Texture* texture, int layer) :
    texture(texture) {
    this->layer = layer;
}

AnimationComponent::~AnimationComponent() {
    SDL_DestroyTexture(this->texture);
}

SDL_Texture* AnimationComponent::getNextTexture(int dt) {
    return this->texture;
}
