#include "artComponent.h"

ObjectAnimationComponent::ObjectAnimationComponent(Entity *entity, SDL_Texture *texture, LayerEnum layer,
                                                   bool movesWithCamera, int fps, int numFrames):
        ArtComponent(entity, layer, movesWithCamera),
        texture(texture),
        timecount(0),
        fps(fps),
        numFrames(numFrames)
{
    this->clip={0,0,32,32};
}

SDL_Texture* ObjectAnimationComponent::getNextTexture(int) {
    return this->texture;
}

SDL_Rect* ObjectAnimationComponent::getNextSrcRect(int dt) {
    timecount+=dt;
    timecount%=1000/fps;
    clip.x = (timecount/(1000/fps/numFrames))*32;
    return &clip;
}