#include <state.h>

PlayState::PlayState(int windowW, int windowH, std::list<Command*>& cmdList,
                     std::map<int, Entity*>& entityMap, SDL_Renderer* renderer,
                     EntityBuilder& entBuilder, DrawingHandler& drawingHandler,
                     InputHandler& inputHandler, SoundHandler& soundHandler,
                     AiHandler& aiHandler, CollisionHandler& collisionHandler) :
    State(cmdList, entityMap, renderer),
    windowW(windowW),
    windowH(windowH),
    entityBuilder(entBuilder),
    drawingHandler(drawingHandler),
    inputHandler(inputHandler),
    soundHandler(soundHandler),
    aiHandler(aiHandler),
    collisionHandler(collisionHandler) {
}

PlayState::~PlayState() {
    if (this->texture)
        SDL_DestroyTexture(this->texture);
}

void PlayState::begin() {
    // Load image
    SDL_Surface* loadedImage = IMG_Load("resources/jhu-logo.png");
    SDL_Surface* finalImage = NULL;
    if (loadedImage == NULL) {
        std::cerr << "Unable to load image! SDL_image Error: "
                  << IMG_GetError() << std::endl;
        return;
    } else {
        finalImage = SDL_ConvertSurface(loadedImage, loadedImage->format, 0);
        if (finalImage == NULL) {
            std::cerr << "Unable to optimize image! SDL Error: "
                      << SDL_GetError() << std::endl;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedImage);
    }
    this->texture = SDL_CreateTextureFromSurface(this->renderer, finalImage);
    this->backgroundRect = centeredRect(this->windowW, this->windowH,
                                        finalImage->w, finalImage->h);
    SDL_FreeSurface(finalImage);

    this->soundHandler.playBackgroundMusic("resources/abstract_tracking.xm");

    // Create entities
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

void PlayState::run() {
    bool running = true;
    float lastTime = SDL_GetTicks();

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        lastTime = currentTime;
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    return;
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
        SDL_RenderCopy(this->renderer, this->texture, NULL, &this->backgroundRect);
        this->drawingHandler.draw(dt);
        SDL_RenderPresent(this->renderer);
    }
}

void PlayState::cleanup() {
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
}
