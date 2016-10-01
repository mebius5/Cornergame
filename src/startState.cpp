#include "state.h"

StartState::StartState(int windowW, int windowH, std::list<Command*>& cmdList,
                       std::map<int, Entity*>& entMap, SDL_Renderer* renderer,
                       EntityBuilder& entBuilder, DrawingHandler& drawer,
                       InputHandler& inputHandler, SoundHandler& soundHandler) :
    State(cmdList, entMap, renderer, windowW, windowH),
    entityBuilder(entBuilder),
    drawingHandler(drawer),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    texture(NULL),
    font(NULL) {
}

StartState::~StartState() {
    if (this->texture)
        SDL_DestroyTexture(this->texture);
    if (this->font)
        TTF_CloseFont(this->font);
}

void StartState::begin() {
    // Load fonts
    this->font = TTF_OpenFont("resources/CaesarDressing-Regular.ttf", 30);
    SDL_Color color={255, 255, 255, 255};
    SDL_Surface* textSurf = TTF_RenderUTF8_Blended(font, "CornerGame", color);
    if (textSurf == NULL) {
        std::cerr << "Unable to load text surface! SDL_image Error: "
                  << IMG_GetError() << std::endl;
        return;
    }

    this->texture = SDL_CreateTextureFromSurface(renderer, textSurf);
    SDL_FreeSurface(textSurf);
    this->textRect = centeredRect(this->windowW, this->windowH, 200, 800);
}

void StartState::run() {
    for (;;) {
        SDL_RenderClear(this->renderer);
        SDL_RenderCopy(this->renderer, this->texture, NULL,&this->textRect);
        this->drawingHandler.draw(5);       //TODO: add timing (dt)
        SDL_RenderPresent(this->renderer);
    }
}

void StartState::cleanup() {
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
    if (this->font) {
        TTF_CloseFont(this->font);
        this->font = NULL;
    }
}
