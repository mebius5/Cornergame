#include <state.h>

PlayState::PlayState(int windowW, int windowH, EntityManager& entityManager,
                     std::list<Command*>& commandList, SDL_Renderer* renderer,
                     DrawingHandler& drawingHandler, InputHandler& inputHandler,
                     SoundHandler& soundHandler, ControlHandler& controlHandler,
                     AiHandler& aiHandler, CollisionHandler& collisionHandler) :
    State(entityManager, commandList, renderer, windowW, windowH),
    drawingHandler(drawingHandler),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    controlHandler(controlHandler),
    aiHandler(aiHandler),
    collisionHandler(collisionHandler) {
}

PlayState::~PlayState() {
}

void PlayState::begin() {
    this->soundHandler.playBackgroundMusic("music/cabin_fever_playscreen.xm");

    // Create entities
    this->entityManager.createBackground("resources/jhu-logo.png",
                                         this->windowW, this->windowH);

    Entity* hero = this->entityManager.createHero(100, 100,
                                           "resources/collision_alert.wav");

    this->entityManager.createEnemy(350, 150);
    this->entityManager.createEnemy(500, 150);
    this->entityManager.createEnemy(650, 150);
    this->entityManager.createEnemy(400, 300);
    this->entityManager.createEnemy(600, 300);

    this->entityManager.createHealthBar(100, 600, 200, 50, hero);
    this->entityManager.createScoreBox(1150, 600, hero);
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
        this->soundHandler.handleSFX(dt);
        this->drawingHandler.draw(dt);

        StateEnum nextState = this->controlHandler.handleStateCommands();
        if (nextState)
            return nextState;
    }

    return STATE_HIGHSCORE;
}

void PlayState::cleanup() {
    this->entityManager.clear();
    this->commandList.clear();
    this->soundHandler.stopBackgroundMusic();
}
