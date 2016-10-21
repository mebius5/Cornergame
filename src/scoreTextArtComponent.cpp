#include "artComponent.h"
#include <iostream>

ScoreTextArtComponent::ScoreTextArtComponent(Entity* entity, SDL_Renderer* renderer,
                                             TTF_Font* font, Entity *owner, int layer):
    ArtComponent(entity, layer, true),
    owner(owner),
    renderer(renderer),
    lastTexture(NULL),
    lastScore(-1),
    font(font) {
}

ScoreTextArtComponent::~ScoreTextArtComponent() {
    this->renderer = NULL;
    if(lastTexture){
        SDL_DestroyTexture(this->lastTexture);
        this->lastTexture = NULL;
    }
}

SDL_Texture* ScoreTextArtComponent::getNextTexture(int) {
    if (this->lastScore!=this->owner->score->getScore()) {
        if (this->lastTexture) {
            SDL_DestroyTexture(this->lastTexture);
            this->lastTexture = NULL;
        }

        this->lastScore = this->owner->score->getScore();

        SDL_Color color = { 255, 255, 255, 255 };
        SDL_Surface* textSurf =
            TTF_RenderUTF8_Blended(this->font, std::to_string(this->lastScore).c_str(), color);
        if (textSurf == NULL) {
            std::cerr << "Blend font failed! TTF Error: " << TTF_GetError() << std::endl;
            return NULL;
        }

        this->lastTexture = SDL_CreateTextureFromSurface(this->renderer, textSurf);
        this->entity->width = textSurf->w;
        this->entity->height = textSurf->h;
        SDL_FreeSurface(textSurf);
    }

    return this->lastTexture;
}

SDL_Rect* ScoreTextArtComponent::getNextSrcRect(int) {
    return NULL;
}
