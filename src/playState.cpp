#include "state.h"

PlayState::PlayState(int windowW, int windowH, EntityManager& entityManager,
                 std::vector<Command*>& commandList, SDL_Renderer* renderer,
                 DrawingHandler& drawingHandler, InputHandler& inputHandler,
                 SoundHandler& soundHandler, ControlHandler& controlHandler,
                 AiHandler& aiHandler, CollisionHandler& collisionHandler,
                 ScoreHandler& scoreHandler, PhysicsHandler& physicsHandler,
                 PowerUpHandler& powerUpHandler, ResultsState& resultsState,
                 HighscoreState& highscoreState) :
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
    resultsState(resultsState),
    highscoreState(highscoreState),
    levelW(0),
    levelH(0){
}

PlayState::~PlayState() {
}

void PlayState::begin(int level) {
    this->soundHandler.playBackgroundMusic(MUSIC_PLAY);
    this->entityManager.createBackground(TEX_BACKGROUND, this->windowW,
                                         this->windowH);

    std::string levelFile = "levels/level";
    levelFile.append(std::to_string(level));
    levelFile.append(".txt");
    Level level1(levelFile.c_str(), windowW, windowH);
    this->entityManager.populateLevel(&level1);
    this->hero = entityManager.heroEntities.at(0);
    this->hero2 = entityManager.heroEntities.at(1);
    this->levelW = level1.width*32;
    this->levelH = level1.height*32;
}

StateEnum PlayState::run() {
    // Run preview
    bool previewOn = true;
    float lastTime = SDL_GetTicks();
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
            return nextState;
    }

    return STATE_HIGHSCORE;
}

void PlayState::cleanup(StateEnum nextState) {
    if (nextState == STATE_RESULTS) {  // if game complete, update other states
        this->highscoreState.updateHighscores(this->hero, this->hero2);
        this->resultsState.updateResults(this->hero, this->hero2);     //TODO: save sprite?
    }
    this->entityManager.clear();
    this->commandList.clear();
    this->soundHandler.stopBackgroundMusic();
    this->drawingHandler.resetCamera(0, 0, windowW,windowH);
}
