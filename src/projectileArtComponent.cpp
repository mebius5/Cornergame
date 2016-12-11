#include "artComponent.h"

ProjectileArtComponent::ProjectileArtComponent(Entity* entity, SDL_Texture* texture) :
    ArtComponent(entity, LAYER_HERO, false),
    texture(texture) {
}

SDL_Texture* ProjectileArtComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* ProjectileArtComponent::getNextSrcRect(int /*dt*/) {
    return NULL;
}

double ProjectileArtComponent::getNextAngle(int /*dt*/) {
    if (entity->physics->xVelocity == 0) {
        return 0;
    } else {
        double angle = atan((double)entity->physics->yVelocity/(double)entity->physics->xVelocity);
        angle *= 180/M_PI;
        return angle;
    }
}

SDL_RendererFlip ProjectileArtComponent::getNextFlip(int /*dt*/) {
    if (entity->physics->xVelocity < 0) {
        return SDL_FLIP_HORIZONTAL;
    } else {
        return SDL_FLIP_NONE;
    }
}