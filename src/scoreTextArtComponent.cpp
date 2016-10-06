#include "artComponent.h"


ScoreTextArtComponent::ScoreTextArtComponent(Entity* entity,
                               SDL_Renderer* renderer, Entity *owner, int layer):
    ArtComponent(entity, layer),
    owner(owner),
    renderer(renderer),
    lastTexture(NULL),
    lastScore(-1){

}

ScoreTextArtComponent::~ScoreTextArtComponent() {
    this->renderer = NULL;
    if(lastTexture){
        SDL_DestroyTexture(this->lastTexture);
        this->lastTexture = NULL;
    }
}

SDL_Surface * ScoreTextArtComponent::loadFont(const char *fontName, const char *text, int fontSize, int r, int g,
                                              int b) {
    TTF_Font * font = TTF_OpenFont(fontName, fontSize);
    SDL_Color color={(Uint8)r,(Uint8) g,(Uint8) b, 255};
    SDL_Surface* textSurf = TTF_RenderUTF8_Blended(font, text, color);
    TTF_CloseFont(font);
    if (textSurf == NULL) {
        std::cerr << "Unable to load font! TTF font Error: "
                  << TTF_GetError() << std::endl;
        return NULL;
    }
    return textSurf;
}

SDL_Texture* ScoreTextArtComponent::getNextTexture(int) {
    if(lastScore!=this->owner->score->getScore()){
        if(this->lastTexture){
            SDL_DestroyTexture(this->lastTexture);
            this->lastTexture = NULL;
        }

        lastScore = this->owner->score->getScore();

        std::string score;
        score = std::to_string(this->lastScore);

        SDL_Surface * tempSurface = loadFont("resources/CaesarDressing-Regular.ttf",
                                             score.c_str(), 36, 255, 255, 255);
        this->lastTexture = SDL_CreateTextureFromSurface(this->renderer, tempSurface);
        this->entity->width = tempSurface->w;
        this->entity->height = tempSurface->h;
        SDL_FreeSurface(tempSurface);
    }

    return this->lastTexture;
}

SDL_Rect* ScoreTextArtComponent::getNextSrcRect(int) {
    return NULL;
}
