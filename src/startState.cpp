#include "state.h"

StartState::StartState(int windowW, int windowH, EntityManager& entityManager,
                std::vector<Command*>& commandList, SDL_Renderer* renderer,
                DrawingHandler& drawingHandler, InputHandler& inputHandler,
                SoundHandler& soundHandler, ControlHandler& controlHandler,
                CollisionHandler& collisionHandler, PhysicsHandler& physicsHandler, ParticleHandler& particleHandler) :
    State(entityManager, commandList, renderer, windowW, windowH),
    drawingHandler(drawingHandler),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    controlHandler(controlHandler),
    collisionHandler(collisionHandler),
    physicsHandler(physicsHandler),
    particleHandler(particleHandler) {
}

void StartState::begin(int /*level*/) {
    Level level1("levels/startScreenLevel.txt", windowW, windowH);
    this->entityManager.populateLevel(&level1);
    Entity * hero = this->entityManager.createHero(TEX_HERO, 500, 608, SFX_NONE, false);
    DynamicCollisionComponent* dcc = static_cast<DynamicCollisionComponent*>(hero->collision);
    dcc->onGround = true;
    dcc->leftBound = 0;
    dcc->rightBound = 1000;

    this->soundHandler.playBackgroundMusic(MUSIC_START);

    this->entityManager.createCenteredFadeInText(
            FONT_GLOBAL, "CornerStone", 100,
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

        this->inputHandler.handleEvents(dt);
        this->physicsHandler.update(dt);
        this->particleHandler.update(dt);
        this->collisionHandler.handleCollisions();
        this->drawingHandler.draw(dt);

        StateEnum nextState = this->controlHandler.handleStateCommands();

        if(nextState==STATE_RESULTS){
            return STATE_MENU;
        }

        if (nextState != STATE_NONE)
            return nextState;

        if(this->controlHandler.isPreviewOff())
            break;

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
