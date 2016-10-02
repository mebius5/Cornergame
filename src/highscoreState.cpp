#include "state.h"

HighscoreState::HighscoreState(int windowW, int windowH, std::list<Command*>& cmdList,
                       std::map<int, Entity*>& entMap, SDL_Renderer* renderer,
                       EntityBuilder& entBuilder, DrawingHandler& drawer,
                       InputHandler& inputHandler, SoundHandler& soundHandler,
                       ControlHandler& controlHandler) :
    State(cmdList, entMap, renderer, windowW, windowH),
    entityBuilder(entBuilder),
    drawingHandler(drawer),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    controlHandler(controlHandler) {
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

        this->inputHandler.handleEvents();
        this->inputHandler.update(dt);
        this->soundHandler.handleSFX(dt);
        this->drawingHandler.draw(dt);

        int nextState = this->controlHandler.handleStateCommands();
        if (nextState)
            return (State::StateEnum)nextState;
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
