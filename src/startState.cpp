#include "state.h"

StartState::StartState(int windowW, int windowH, EntityManager& entityManager,
                std::vector<Command*>& commandList, SDL_Renderer* renderer,
                DrawingHandler& drawingHandler, InputHandler& inputHandler,
                SoundHandler& soundHandler, ControlHandler& controlHandler,
                CollisionHandler& collisionHandler, PhysicsHandler& physicsHandler) :
    State(entityManager, commandList, renderer, windowW, windowH),
    drawingHandler(drawingHandler),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    controlHandler(controlHandler),
    collisionHandler(collisionHandler),
    physicsHandler(physicsHandler) {
}

StartState::~StartState() {
}

void StartState::begin(int) {
    Level level1("levels/startScreenLevel.txt", windowW, windowH);
    this->entityManager.populateLevel(&level1);
    this->entityManager.createHero(TEX_HERO, 500, 200, SFX_NONE, false);

    this->soundHandler.playBackgroundMusic(MUSIC_START);

    this->entityManager.createCenteredFadeInText(
            FONT_GLOBAL, "CornerGame", 100,
            255, 255, 255, 0, this->windowW, this->windowH);
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
        this->physicsHandler.update(dt);
        this->collisionHandler.handleCollisions(0);
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
    this->drawingHandler.resetCamera(0, 0, windowW, windowH);
}
