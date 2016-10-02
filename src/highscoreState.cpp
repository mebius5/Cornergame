#include "state.h"

HighscoreState::HighscoreState(int windowW, int windowH, std::list<Command*>& cmdList,
                       std::map<int, Entity*>& entMap, SDL_Renderer* renderer,
                       EntityBuilder& entBuilder, DrawingHandler& drawer,
                       InputHandler& inputHandler, SoundHandler& soundHandler) :
    State(cmdList, entMap, renderer, windowW, windowH),
    entityBuilder(entBuilder),
    drawingHandler(drawer),
    inputHandler(inputHandler),
    soundHandler(soundHandler) {
}

HighscoreState::~HighscoreState() {
}

void HighscoreState::begin() {
    // play background music
    this->soundHandler.playBackgroundMusic("music/ambient_starfield_highscore.xm");

    Entity * mainText = entityBuilder.createCenteredFadeInText("resources/CaesarDressing-Regular.ttf", "High Scores:",
                                                               100,
                                                               255, 255, 255, 0, this->windowW, this->windowH);
    entityMap.operator[](mainText->getId())= mainText;
}

State::StateEnum HighscoreState::run() {
    bool running = true;
    float lastTime = SDL_GetTicks();

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return State::StateEnum::QUIT;
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    return State::StateEnum::QUIT;
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

    return State::StateEnum::MENU;
}

void HighscoreState::cleanup() {
    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        delete it->second;      // delete Entities from map
    }
    entityMap.clear();
    commandList.clear();

    this->soundHandler.stopBackgroundMusic();
}
