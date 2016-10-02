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
    /***
    if (this->texture)
        SDL_DestroyTexture(this->texture);
    if (this->font)
        TTF_CloseFont(this->font);
        ***/
}

void StartState::begin() {
    // play background music
    this->soundHandler.playBackgroundMusic("music/mega_destruction_titlescreen.xm");

    // Load fonts
    this->font = TTF_OpenFont("resources/CaesarDressing-Regular.ttf", 100);
    SDL_Color color={255, 255, 255, 255};
    SDL_Surface* textSurf = TTF_RenderUTF8_Blended(font, "CornerGame", color);
    if (textSurf == NULL) {
        std::cerr << "Unable to load text surface! SDL_image Error: "
                  << IMG_GetError() << std::endl;
        return;
    }
    SDL_SetSurfaceAlphaMod(textSurf, 128);

    this->texture = SDL_CreateTextureFromSurface(renderer, textSurf);
    this->textRect = centeredRect(this->windowW, this->windowH, textSurf->w, textSurf->h);
    SDL_FreeSurface(textSurf);
}

void StartState::run() {

    bool running = true;
    float lastTime = SDL_GetTicks();

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    return;
                else
                    this->inputHandler.handleEvent(event);
            } else {
                this->inputHandler.handleEvent(event);
            }
        }

        this->inputHandler.update(dt);
        this->soundHandler.handleSFX(dt);

        SDL_RenderClear(this->renderer);
        SDL_RenderCopy(this->renderer, this->texture, NULL,&this->textRect);
        this->drawingHandler.draw(dt);

        SDL_RenderPresent(this->renderer);

    }
}

void StartState::cleanup() {
    this->soundHandler.stopBackgroundMusic();

    if (this->texture) {
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
    if (this->font) {
        TTF_CloseFont(this->font);
        this->font = NULL;
    }

}
