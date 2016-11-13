#include "artComponent.h"

// NOTE: not currently in Makefile, not updated to current ScoreComponent
ScoreTextArtComponent::ScoreTextArtComponent(Entity* entity, SDL_Renderer* renderer,
                            TTF_Font* font, ScoreComponent *ownerScore, int layer):
    ArtComponent(entity, layer, true),
    ownerScore(ownerScore),
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
    if (this->lastScore!=this->ownerScore->getScore()) {
        if (this->lastTexture) {
            SDL_DestroyTexture(this->lastTexture);
            this->lastTexture = NULL;
        }

        this->lastScore = this->ownerScore->getScore();

        SDL_Color color = { 255, 255, 255, 255 };
        SDL_Surface* textSurf =
            TTF_RenderUTF8_Blended(this->font, std::to_string(this->lastScore).c_str(), color);
        if (textSurf == NULL) {
            std::cerr << "Blend font failed! TTF Error: " << TTF_GetError() << std::endl;
            return NULL;
        }

        this->lastTexture = SDL_CreateTextureFromSurface(this->renderer, textSurf);
        this->entity->drawWidth = textSurf->w;
        this->entity->drawHeight = textSurf->h;
        SDL_FreeSurface(textSurf);
    }

    return this->lastTexture;
}

SDL_Rect* ScoreTextArtComponent::getNextSrcRect(int) {
    return NULL;
}
