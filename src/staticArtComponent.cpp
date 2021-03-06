#include "artComponent.h"

StaticArtComponent::StaticArtComponent(Entity* ent, SDL_Texture* tex,
                                       LayerEnum layer, bool movesWithCamera) :
    ArtComponent(ent, layer, movesWithCamera),
    texture(tex)
{
}

SDL_Texture* StaticArtComponent::getNextTexture(int /*dt*/) {
    return this->texture;
}

SDL_Rect* StaticArtComponent::getNextSrcRect(int /*dt*/) {
    return NULL;
}

SDL_RendererFlip StaticArtComponent::getNextFlip(int /*dt*/) {
	if (entity->rotates) {
		return SDL_FLIP_HORIZONTAL;
	} else {
		return SDL_FLIP_NONE;
	}
}