#include "artComponent.h"

TextFadeInComponent::TextFadeInComponent(Entity* entity, SDL_Renderer *renderer,
                                         SDL_Surface *surface, float initialAlpha):
    ArtComponent(entity, LAYER_TEXT, false),
    surface(surface),
    renderer(renderer),
    alpha(initialAlpha) {
//    SDL_SetSurfaceAlphaMod(this->surface, (int)this->alpha);
    this->lastTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
}

TextFadeInComponent::~TextFadeInComponent() {
    if (this->surface)
        SDL_FreeSurface(this->surface);
    if (this->lastTexture)
        SDL_DestroyTexture(this->lastTexture);
}

/* Need to destroy texture after use */
SDL_Texture* TextFadeInComponent::getNextTexture(int dt) {
    if (this->alpha < 255.0f) {     // reconstruct texture if necessary
        this->alpha += dt / 8.0f;
        this->alpha = std::min(this->alpha, 255.0f);
        SDL_SetSurfaceAlphaMod(this->surface, (int)this->alpha);

        if (this->lastTexture)      // destroy the previously created texture
            SDL_DestroyTexture(this->lastTexture);
        this->lastTexture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
    }
    return this->lastTexture;
}


SDL_Rect* TextFadeInComponent::getNextSrcRect(int /*dt*/) {
    return NULL;
}

void TextFadeInComponent::selectMenuItem() {
    SDL_SetSurfaceColorMod(this->surface, (Uint8)255, (Uint8)0, (Uint8)0);
    this->alpha = std::max(this->alpha - 1.0f, 0.0f);
}

void TextFadeInComponent::deselectMenuItem() {
    SDL_SetSurfaceColorMod(this->surface, (Uint8)255, (Uint8)255, (Uint8)255);
    this->alpha = std::max(this->alpha - 1.0f, 0.0f);
}
