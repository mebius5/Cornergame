#include "state.h"
#include <iostream>

StartState::StartState(int windowW, int windowH, EntityManager& entityManager,
                std::vector<Command*>& commandList, SDL_Renderer* renderer,
                DrawingHandler& drawingHandler, InputHandler& inputHandler,
                SoundHandler& soundHandler, ControlHandler& controlHandler,
                CollisionHandler& collisionHandler) :
    State(entityManager, commandList, renderer, windowW, windowH),
    drawingHandler(drawingHandler),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    controlHandler(controlHandler),
    collisionHandler(collisionHandler) {
}

StartState::~StartState() {
}

void StartState::begin() {
    this->soundHandler.playBackgroundMusic(MUSIC_START);

    this->entityManager.createCenteredFadeInText(
                        "resources/CaesarDressing-Regular.ttf", "CornerGame",
                        100,
                        255, 255, 255, 0, this->windowW, this->windowH);

    this->entityManager.createHero(500, 500, SFX_NONE, false);
    Level level1("levels/startScreenLevel.txt");
    this->entityManager.populateLevel(&level1);
}

StateEnum StartState::run() {
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
        this->collisionHandler.handleCollisions();
        this->drawingHandler.draw(dt);

        StateEnum nextState = this->controlHandler.handleStateCommands();
        if (nextState != STATE_NONE)
            return nextState;

        if (milliSecElapsed >= 10000)    // Return menu after 10 sec
            break;
    }
    return STATE_MENU;
}

void StartState::cleanup(StateEnum /*next*/) {
    this->entityManager.clear();
    this->commandList.clear();
    this->soundHandler.stopBackgroundMusic();
    this->drawingHandler.resetCamera(windowW, windowH);
}
