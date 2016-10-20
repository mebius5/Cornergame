#include <state.h>
#include <iostream>
PlayState::PlayState(int windowW, int windowH, EntityManager& entityManager,
                 std::vector<Command*>& commandList, SDL_Renderer* renderer,
                 DrawingHandler& drawingHandler, InputHandler& inputHandler,
                 SoundHandler& soundHandler, ControlHandler& controlHandler,
                 AiHandler& aiHandler, CollisionHandler& collisionHandler,
                 ScoreHandler& scoreHandler, PhysicsHandler& physicsHandler,
                 ResultsState& resultsState, HighscoreState& highscoreState) :
    State(entityManager, commandList, renderer, windowW, windowH),
    drawingHandler(drawingHandler),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    controlHandler(controlHandler),
    aiHandler(aiHandler),
    collisionHandler(collisionHandler),
    scoreHandler(scoreHandler),
    resultsState(resultsState),
    highscoreState(highscoreState),
    physicsHandler(physicsHandler) {
}

PlayState::~PlayState() {
}

void PlayState::begin(int level) {
    // Play background music
    this->soundHandler.playBackgroundMusic(MUSIC_PLAY);

    // Create background
    this->entityManager.createBackground("resources/jhu-logo.png",
                                         this->windowW, this->windowH);

    /***
    Entity * hero2 = this->entityManager.createHero(100, 250, SFX_ALERT, true);
    this->entityManager.createHealthBar(100, 600, 200, 40, hero2);
    this->entityManager.createScoreBox(850, 600, hero2);


    this->entityManager.createEnemy(350, 150);
    this->entityManager.createEnemy(500, 150);
    this->entityManager.createEnemy(650, 150);
    this->entityManager.createEnemy(400, 300);
    this->entityManager.createEnemy(600, 300);


    this->entityManager.createVictoryZone(1150, 200);
      ****/

    std::string levelFile = "levels/level";
    levelFile.append(std::to_string(level));
    levelFile.append(".txt");
    Level level1(levelFile.c_str(), windowW, windowH);
    this->entityManager.populateLevel(&level1);
    drawingHandler.initializeCamera(level1.width*32, level1.height*32);
    this->hero = entityManager.heroEntities.at(0);
}

StateEnum PlayState::run() {
    bool running = true;
    float lastTime = SDL_GetTicks();

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;

        //std::cout << this->hero->xVelocity << "  " << this->hero->yVelocity << "\n" << std::endl;
        this->aiHandler.updateAi(dt);
        this->entityManager.handleSpawns();
        this->inputHandler.handleEvents();
        this->physicsHandler.update(dt);
        this->collisionHandler.handleCollisions();
        this->soundHandler.handleSfx(dt);
        this->scoreHandler.handleScore(dt);
        this->drawingHandler.shift(dt);
        this->drawingHandler.draw(dt);

        StateEnum nextState = this->controlHandler.handleStateCommands();
        if (nextState)
            return nextState;
    }

    return STATE_HIGHSCORE;
}

void PlayState::cleanup(StateEnum nextState) {
    if (nextState == STATE_RESULTS) {  // if game complete, update other states
        this->highscoreState.updateHighscores(this->hero);
        this->resultsState.updateResults(this->hero);     //TODO: save sprite?
    }
    this->entityManager.clear();
    this->commandList.clear();
    this->soundHandler.stopBackgroundMusic();
    this->drawingHandler.resetCamera(windowW,windowH);
}
