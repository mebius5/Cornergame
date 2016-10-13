#include <state.h>

PlayState::PlayState(int windowW, int windowH, EntityManager& entityManager,
                 std::vector<Command*>& commandList, SDL_Renderer* renderer,
                 DrawingHandler& drawingHandler, InputHandler& inputHandler,
                 SoundHandler& soundHandler, ControlHandler& controlHandler,
                 AiHandler& aiHandler, CollisionHandler& collisionHandler, ScoreHandler& scoreHandler,
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
    highscoreState(highscoreState) {
        this->level = new Level("levels/level1.txt");
}

PlayState::~PlayState() {
}

void PlayState::begin() {
    this->soundHandler.playBackgroundMusic(MUSIC_PLAY);

    // Create entities
    this->entityManager.createBackground("resources/jhu-logo.png",
                                         this->windowW, this->windowH);

    this->hero = this->entityManager.createHero(100, 150, SFX_ALERT, false);
    this->entityManager.createHealthBar(100, 100, 200, 40, hero);
    this->entityManager.createScoreBox(850, 100, hero);

    /***
    Entity * hero2 = this->entityManager.createHero(100, 250, SFX_ALERT, true);
    this->entityManager.createHealthBar(100, 600, 200, 40, hero2);
    this->entityManager.createScoreBox(850, 600, hero2);
    ****/

    this->entityManager.createEnemy(350, 150);
    this->entityManager.createEnemy(500, 150);
    this->entityManager.createEnemy(650, 150);
    this->entityManager.createEnemy(400, 300);
    this->entityManager.createEnemy(600, 300);


    this->entityManager.createVictoryZone(1150, 200);


    for(int i = 0; i < this->level->height; i++){
        for(int j = 0; j < this->level->width; j++){
            if (this->level->getTile(i, j) == TERRAIN) {
                this->entityManager.createTerrain(j * 32, i * 32);
            }
        }
    }

    /*** Can use this to disable border handling in collision handler
    this->entityManager.createTerrain(0,0,windowW,1);
    this->entityManager.createTerrain(0,0,1,windowH);
    this->entityManager.createTerrain(windowW,0,1,windowH);
    this->entityManager.createTerrain(0,windowH,windowW,1);
     ***/
}

StateEnum PlayState::run() {
    bool running = true;
    float lastTime = SDL_GetTicks();

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;

        this->aiHandler.updateAi(dt);
        this->inputHandler.handleEvents();
        this->inputHandler.update(dt);
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
