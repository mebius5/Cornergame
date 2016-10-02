#include <state.h>

PlayState::PlayState(int windowW, int windowH, std::list<Command*>& cmdList,
                     std::map<int, Entity*>& entityMap, SDL_Renderer* renderer,
                     EntityBuilder& entBuilder, DrawingHandler& drawingHandler,
                     InputHandler& inputHandler, SoundHandler& soundHandler,
                     AiHandler& aiHandler, CollisionHandler& collisionHandler) :
    State(cmdList, entityMap, renderer, windowW, windowH),
    entityBuilder(entBuilder),
    drawingHandler(drawingHandler),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    aiHandler(aiHandler),
    collisionHandler(collisionHandler) {
}

PlayState::~PlayState() {
}

void PlayState::begin() {
    //Play background music
    this->soundHandler.playBackgroundMusic("music/cabin_fever_playscreen.xm");

    // Create entities

    Entity * background = this->entityBuilder.createBackground("resources/jhu-logo.png",
                                                               this->windowW, this->windowH);
    this->entityMap.operator[](background->getId()) = background;

    Entity* hero = this->entityBuilder.createHero(100, 100,
                                            "resources/collision_alert.wav");
    this->entityMap.operator[](hero->getId()) = hero;

    Entity* enemy1 = this->entityBuilder.createEnemy(350,150);
    this->entityMap.operator[](enemy1->getId()) = enemy1;

    Entity* enemy2 = this->entityBuilder.createEnemy(500,150);
    this->entityMap.operator[](enemy2->getId()) = enemy2;

    Entity* enemy3 = this->entityBuilder.createEnemy(650,150);
    this->entityMap.operator[](enemy3->getId()) = enemy3;

    Entity* enemy4 = this->entityBuilder.createEnemy(400,300);
    this->entityMap.operator[](enemy4->getId()) = enemy4;

    Entity* enemy5 = this->entityBuilder.createEnemy(600,300);
    this->entityMap.operator[](enemy5->getId()) = enemy5;
}

StateEnum PlayState::run() {
    bool running = true;
    float lastTime = SDL_GetTicks();

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return QUIT;
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    return QUIT;
                else
                    this->inputHandler.handleEvent(event);
            } else {
                this->inputHandler.handleEvent(event);
            }
        }

        this->aiHandler.handleAiCommands();
        this->aiHandler.update(dt);
        this->inputHandler.update(dt);
        this->collisionHandler.handleCollisions();
        this->soundHandler.handleSFX(dt);

        SDL_RenderClear(this->renderer);

        this->drawingHandler.draw(dt);

        SDL_RenderPresent(this->renderer);
    }

    return HIGHSCORE;
}

void PlayState::cleanup() {
    this->soundHandler.stopBackgroundMusic();
}
