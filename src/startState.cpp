#include "state.h"

StartState::StartState(int windowW, int windowH, std::list<Command*>& cmdList,
                       std::map<int, Entity*>& entMap, SDL_Renderer* renderer,
                       EntityBuilder& entBuilder, DrawingHandler& drawer,
                       InputHandler& inputHandler, SoundHandler& soundHandler) :
    State(cmdList, entMap, renderer, windowW, windowH),
    entityBuilder(entBuilder),
    drawingHandler(drawer),
    inputHandler(inputHandler),
    soundHandler(soundHandler) {
}

StartState::~StartState() {
}

void StartState::begin() {
    // play background music
    this->soundHandler.playBackgroundMusic("music/mega_destruction_titlescreen.xm");

    Entity * mainText = entityBuilder.createCenteredFadeInText("resources/CaesarDressing-Regular.ttf", "CornerGame",
                                                               100,
                                                               255, 255, 255, 0, this->windowW, this->windowH);
    entityMap.operator[](mainText->getId())= mainText;
}

StateEnum StartState::run() {
    bool running = true;
    float lastTime = SDL_GetTicks();

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return QUIT;
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    return QUIT;
                } else
                    this->inputHandler.handleEvent(event);
            } else {
                this->inputHandler.handleEvent(event);
            }
        }

        this->inputHandler.update(dt);
        this->soundHandler.handleSFX(dt);

        SDL_RenderClear(this->renderer);

        this->drawingHandler.draw(dt);

        SDL_RenderPresent(this->renderer);

    }
    return MENU;
}

void StartState::cleanup() {
    this->soundHandler.stopBackgroundMusic();
}
