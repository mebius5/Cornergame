#include "artComponent.h"

BackgroundArtComponent::BackgroundArtComponent(Entity* ent, SDL_Texture* tex, int lay, float speed) :
    ArtComponent(ent, lay, false),
    texture(tex),
    speed(speed) {
}

SDL_Texture* BackgroundArtComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* BackgroundArtComponent::getNextSrcRect(int /*dt*/) {
    return NULL;
}

void BackgroundArtComponent::shift(float cameraXShift) {

}
