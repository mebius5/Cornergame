
#include "state.h"

StartState::StartState(SDL_Renderer * renderer, int windowW, int windowH, std::list<Command*> * commandList,
                       std::map<int, Entity*> * entityMap, DrawingHandler * drawingHandler,
                       EntityBuilder * entityBuilder, InputHandler * inputHandler,
                       SoundHandler * soundHandler){
    this->width = windowW;
    this->height = windowH;
    this->renderer = renderer;
    this->commandList = commandList;
    this->entityMap = entityMap;
    this->drawer = drawingHandler;
    this->entityBuilder = entityBuilder;
    this->inputHandler = inputHandler;
    this->soundHandler = soundHandler;
    this->texture = NULL;
    this->font = NULL;
}

StartState::~StartState() {

    if(this->texture){
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
    if(this->font){
        TTF_CloseFont(this->font);
        this->font = NULL;
    }

    this->drawer = NULL;
    this->entityBuilder = NULL;
    this->inputHandler = NULL;
    this->soundHandler = NULL;
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
    this->textRect = centeredRect(this->width, this->height, 200, 500);
}

void StartState::run() {
    for (;;) {
        SDL_RenderClear(this->renderer);
        SDL_RenderCopy(this->renderer, this->texture, NULL,&this->textRect);
        drawer->draw(this->entityMap, 5);       //TODO: add timing (dt)
        SDL_RenderPresent(this->renderer);
    }
}

void StartState::cleanup() {
    if(this->texture!=NULL){
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
    if(this->font !=NULL){
        TTF_CloseFont(this->font);
        this->font = NULL;
    }
}
