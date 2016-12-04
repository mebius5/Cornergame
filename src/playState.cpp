#include "state.h"

PlayState::PlayState(int windowW, int windowH, EntityManager& entityManager,
                 std::vector<Command*>& commandList, SDL_Renderer* renderer,
                 DrawingHandler& drawingHandler, InputHandler& inputHandler,
                 SoundHandler& soundHandler, ControlHandler& controlHandler,
                 AiHandler& aiHandler, CollisionHandler& collisionHandler,
                 ScoreHandler& scoreHandler, PhysicsHandler& physicsHandler,
                 PowerUpHandler& powerUpHandler, TimeHandler& timeHandler,
                 ResultsState& resultsState, HighscoreState& highscoreState) :
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
    timeHandler(timeHandler),
    resultsState(resultsState),
    highscoreState(highscoreState),
    levelW(0),
    levelH(0),
    p1wins(0),
    p2wins(0) {
}

void PlayState::begin(int levelnum) {
    this->soundHandler.playBackgroundMusic(MUSIC_PLAY);

    if(levelnum%2==1){ //Light theme for even levels
        this->entityManager.createBackground(TEX_BACKGROUND1, 0, 0, 0.25);
        this->entityManager.createBackground(TEX_BACKGROUND2, 0, 0, 0.5);
    } else { //Dark theme for odd levels
        this->entityManager.createBackground(TEX_DARKBACKGROUND1,0,0,0.25);
        this->entityManager.createBackground(TEX_BACKGROUND2, 0, 0, 0.5);
    }

    Level level(levelnum, windowW, windowH);
    this->entityManager.populateLevel(&level);
    this->entityManager.initRespawns();
    this->hero1 = entityManager.heroEntities[0];
    this->hero2 = entityManager.heroEntities[1];
    //if (levelnum != 1) {
        this->hero1->score->wins = this->p1wins;
        this->hero2->score->wins = this->p2wins;
    //}
    this->levelW = level.width * 32;
    this->levelH = level.height * 32;
}

StateEnum PlayState::run() {
    // Run preview
    bool previewOn = true;
    float lastTime = SDL_GetTicks();
    drawingHandler.resetCamera(this->levelW-windowW, this->levelH-windowH, this->levelW, this->levelH);
    drawingHandler.initializeCamera(this->levelW, this->levelH, true);
    while (previewOn) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;

        previewOn=drawingHandler.previewLevel(dt);
        drawingHandler.draw(dt);
        this->inputHandler.handleEvents(dt);
        if (this->controlHandler.isPreviewOff())
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

        // freeze time if necessary
        this->timeHandler.handleTimeCommands();
        dt = this->timeHandler.forward(dt);
        if (dt > 0) {
            this->aiHandler.updateAi(dt);
            this->inputHandler.handleEvents(dt);
            this->physicsHandler.update(dt);
            this->collisionHandler.handleCollisions();
            this->scoreHandler.handleScore(dt);
            this->drawingHandler.checkCameraShakes();
            this->powerUpHandler.update(dt);
            this->drawingHandler.shift(dt);
            this->drawingHandler.draw(dt);
            this->soundHandler.handleSfx(dt);
            this->entityManager.handleSpawns();
            this->entityManager.cleanupEntities();

            StateEnum nextState = this->controlHandler.handleStateCommands();
            if (nextState != STATE_NONE)
                return nextState;
        }
    }

    return STATE_RESULTS; //Unreachable, but necessary to suppress warning
}

void PlayState::cleanup(StateEnum nextState) {
    if (nextState == STATE_RESULTS) {  // if game complete, update other states
        this->entityManager.hideEntity(this->hero1->getId());
        this->entityManager.hideEntity(this->hero2->getId());
        this->highscoreState.updateHighscores(this->hero1, this->hero2);
        this->resultsState.updateResults(this->hero1, this->hero2);
    }
    this->p1wins = this->hero1->score->wins;
    this->p2wins = this->hero2->score->wins;
    this->entityManager.clear();
    this->commandList.clear();
    this->soundHandler.stopBackgroundMusic();
    this->soundHandler.stopAllSfx();
    this->drawingHandler.resetCamera(0, 0, windowW, windowH);
    this->timeHandler.stopSlowMotion();
}