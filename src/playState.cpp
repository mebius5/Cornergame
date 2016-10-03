#include <state.h>

PlayState::PlayState(int windowW, int windowH, std::list<Command*>& cmdList,
                     std::map<int, Entity*>& entityMap, SDL_Renderer* renderer,
                     EntityBuilder& entBuilder, DrawingHandler& drawingHandler,
                     InputHandler& inputHandler, SoundHandler& soundHandler,
                     ControlHandler& controlHandler, AiHandler& aiHandler,
                     CollisionHandler& collisionHandler) :
    State(cmdList, entityMap, renderer, windowW, windowH),
    entityBuilder(entBuilder),
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
    Entity * background = this->entityBuilder.createBackground("resources/jhu-logo.png",
                                                               this->windowW, this->windowH);
    this->entityMap[background->getId()] = background;

    Entity* hero = this->entityBuilder.createHero(100, 100, "resources/collision_alert.wav");
    this->entityMap[hero->getId()] = hero;

    Entity* enemy1 = this->entityBuilder.createEnemy(350, 150);
    this->entityMap[enemy1->getId()] = enemy1;

    Entity* enemy2 = this->entityBuilder.createEnemy(500, 150);
    this->entityMap[enemy2->getId()] = enemy2;

    Entity* enemy3 = this->entityBuilder.createEnemy(650, 150);
    this->entityMap[enemy3->getId()] = enemy3;

    Entity* enemy4 = this->entityBuilder.createEnemy(400, 300);
    this->entityMap[enemy4->getId()] = enemy4;

    Entity* enemy5 = this->entityBuilder.createEnemy(600, 300);
    this->entityMap[enemy5->getId()] = enemy5;
}

StateEnum PlayState::run() {
    bool running = true;
    float lastTime = SDL_GetTicks();

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;

        this->aiHandler.handleAiCommands();
        this->aiHandler.update(dt);
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
    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        delete it->second;      // delete Entities from map
    }
    entityMap.clear();
    commandList.clear();

    this->soundHandler.stopBackgroundMusic();
}
