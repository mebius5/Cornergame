#include "artComponent.h"

TextFadeInComponent::TextFadeInComponent(SDL_Renderer *renderer,
                                         SDL_Surface *surface,
                                         int layer, int initialAlpha):
        surface(surface),
        renderer(renderer),
        lastTexture(NULL),
        initialAlpha((double)initialAlpha) {
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
    this->initialAlpha += ((double) dt/10);
    if(initialAlpha>255){
        initialAlpha=255;
    }
    SDL_SetSurfaceAlphaMod(this->surface,(int)this->initialAlpha);

    if(this->lastTexture){ //Destroy the previously created texture
        SDL_DestroyTexture(this->lastTexture);
        this->lastTexture=NULL;
    }

    this->lastTexture = SDL_CreateTextureFromSurface(this->renderer,this->surface);

    return this->lastTexture;
}

