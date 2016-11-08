#include "state.h"

TutorialState::TutorialState(int windowW, int windowH, EntityManager &entityManager,
                             std::vector<Command *> &commandList, SDL_Renderer *renderer,
                             DrawingHandler &drawingHandler, InputHandler &inputHandler, SoundHandler &soundHandler,
                             ControlHandler &controlHandler, AiHandler &aiHandler, CollisionHandler &collisionHandler,
                             ScoreHandler &scoreHandler, PhysicsHandler &physicsHandler,
                             PowerUpHandler &powerUpHandler):
        State(entityManager, commandList, renderer, windowW, windowH),
        drawingHandler(drawingHandler),
        inputHandler(inputHandler),
        soundHandler(soundHandler),
        controlHandler(controlHandler),
        aiHandler(aiHandler),
        collisionHandler(collisionHandler),
        scoreHandler(scoreHandler),
        physicsHandler(physicsHandler),
        powerUpHandler(powerUpHandler),
        levelW(0),
        levelH(0){
}

void TutorialState::begin(int) {
    this->soundHandler.playBackgroundMusic(MUSIC_PLAY);
    this->entityManager.createBackground(TEX_BACKGROUND, this->windowW,
                                         this->windowH);

    std::string levelFile = "levels/tutorial.txt";
    Level level1(levelFile.c_str(), windowW, windowH);
    this->entityManager.populateLevel(&level1);
    this->hero = entityManager.heroEntities.at(0);
    this->hero2 = entityManager.heroEntities.at(1);
    this->levelW = level1.width*32;
    this->levelH = level1.height*32;
}

StateEnum TutorialState::run() {

    float lastTime = SDL_GetTicks();

    // Run preview
    bool previewOn = true;
    drawingHandler.resetCamera(this->levelW-windowW, this->levelH-windowH, this->levelW, this->levelH);
    drawingHandler.initializeCamera(this->levelW, this->levelH, true);
    while(previewOn){
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;

        previewOn=drawingHandler.previewLevel(dt);
        drawingHandler.draw(dt);
        this->inputHandler.handleEvents(dt);
        if(this->controlHandler.isPreviewOff())
            break;
        StateEnum nextState = this->controlHandler.handleStateCommands();
        if (nextState != STATE_NONE)
            return nextState;
    }

    // Start Gameplay
    drawingHandler.initializeCamera(this->levelW, this->levelH, false);
    drawingHandler.resetCamera(windowW, 0, 2*windowW, windowH);

    bool running = true;
    lastTime = SDL_GetTicks();

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;

        this->aiHandler.updateAi(dt);
        this->inputHandler.handleEvents(dt);
        this->physicsHandler.update(dt);
        this->collisionHandler.handleCollisions();
        this->soundHandler.handleSfx(dt);
        this->scoreHandler.handleScore(dt);
        this->drawingHandler.checkCameraShakes();
        this->powerUpHandler.update(dt);
        this->drawingHandler.shift(dt);
        this->drawingHandler.draw(dt);
        this->entityManager.handleSpawns();
        this->entityManager.cleanupEntities();

        StateEnum nextState = this->controlHandler.handleStateCommands();
        if (nextState != STATE_NONE)
            break;
    }

    return STATE_MENU;
}

void TutorialState::cleanup(StateEnum) {
    this->entityManager.clear();
    this->commandList.clear();
    this->soundHandler.stopBackgroundMusic();
    this->drawingHandler.resetCamera(0, 0, windowW,windowH);
}
