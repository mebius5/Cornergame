#include "state.h"

StartState::StartState(int windowW, int windowH, std::list<Command*>& cmdList,
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

StartState::~StartState() {
}

void StartState::begin() {
    // play background music
    this->soundHandler.playBackgroundMusic("music/mega_destruction_titlescreen.xm");

    Entity * mainText = entityBuilder.createCenteredFadeInText(
                        "resources/CaesarDressing-Regular.ttf", "CornerGame",
                        100,
                        255, 255, 255, 0, this->windowW, this->windowH);
    entityMap.operator[](mainText->getId())= mainText;


    Entity* hero = this->entityBuilder.createHero(500, 500,
                                                  "resources/collision_alert.wav");
    this->entityMap.operator[](hero->getId()) = hero;

}

State::StateEnum StartState::run() {
    bool running = true;
    float lastTime = SDL_GetTicks();
    int milliSecElapsed = 0;

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;
        milliSecElapsed += dt;

        this->inputHandler.handleEvents();
        this->inputHandler.update(dt);
        this->soundHandler.handleSFX(dt);;
        this->drawingHandler.draw(dt);

        int nextState = this->controlHandler.handleStateCommands();
        if (nextState)
            return (State::StateEnum)nextState;

        if (milliSecElapsed>=10000)    //Return menu after 10 sec
            break;
    }
    return State::StateEnum::MENU;
}

void StartState::cleanup() {
    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        delete it->second;      // delete Entities from map
    }
    entityMap.clear();
    commandList.clear();

    this->soundHandler.stopBackgroundMusic();
}
