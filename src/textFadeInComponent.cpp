#include "artComponent.h"

TextFadeInComponent::TextFadeInComponent(SDL_Renderer *renderer,
                                         SDL_Surface *surface,
                                         int layer, int initialAlpha):
        surface(surface),
        renderer(renderer),
        lastTexture(NULL),
        alpha((double)initialAlpha) {
    this->layer = layer;
}

TextFadeInComponent::~TextFadeInComponent() {
    if(this->surface){
        SDL_FreeSurface(this->surface);
        this->surface=NULL;
    }
    if(this->lastTexture){
        SDL_DestroyTexture(this->lastTexture);
        this->lastTexture=NULL;
    }
}

/* Need to destroy texture after use */
SDL_Texture * TextFadeInComponent::getNextTexture(int dt) {
    this->alpha += (double) dt/10;
    if (this->alpha>255)
        this->alpha=255;
    SDL_SetSurfaceAlphaMod(this->surface,(int)this->alpha);

    if (this->lastTexture) { //Destroy the previously created texture
        SDL_DestroyTexture(this->lastTexture);
        this->lastTexture=NULL;
    }

    this->lastTexture = SDL_CreateTextureFromSurface(this->renderer,this->surface);

    return this->lastTexture;
}


SDL_Rect* TextFadeInComponent::getNextSrcRect(int dt) {
    return NULL;
}

void TextFadeInComponent::selectMenuItem() {
    SDL_SetSurfaceColorMod(this->surface, (Uint8) 255, (Uint8)0, (Uint8) 0);
}

void TextFadeInComponent::deselectMenuItem() {
    SDL_SetSurfaceColorMod(this->surface, (Uint8) 255, (Uint8)255, (Uint8) 255);
}
