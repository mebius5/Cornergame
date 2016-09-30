#include <state.h>

PlayState::PlayState(SDL_Renderer * renderer, int windowW, int windowH, std::list<Command*> * commandList,
                     std::map<int, Entity*> * entityMap, DrawingHandler * drawingHandler,
                     EntityBuilder * entityBuilder, InputHandler * inputHandler, AiHandler * aiHandler,
                     CollisionHandler * collisionHandler, SoundHandler * soundHandler) {
    this->renderer = renderer;
    this->windowW = windowW;
    this->windowH = windowH;
    this->commandList = commandList;
    this->entityMap = entityMap;
    this->drawer = drawingHandler;
    this->entityBuilder = entityBuilder;
    this->inputHandler = inputHandler;
    this->aiHandler = aiHandler;
    this->collisionHandler = collisionHandler;
    this->soundHandler = soundHandler;
    this->texture = NULL;
}


PlayState::~PlayState() {
    if(this->texture!=NULL){
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
    this->drawer = NULL;
    this->entityBuilder = NULL;
    this->inputHandler = NULL;
    this->aiHandler = NULL;
    this->collisionHandler = NULL;
    this->soundHandler = NULL;
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

    this->soundHandler->playBackgroundMusic("resources/abstract_tracking.xm");

    // Create hero entity
    Entity* hero = this->entityBuilder->createHero(100, 100,
                                                   "resources/collision_alert.wav");

    this->entityMap->operator[](hero->getId()) = hero;

    //Create enemy entities
    Entity * enemy1 = this->entityBuilder->createEnemy(350,150);
    this->entityMap->operator[](enemy1->getId()) = enemy1;

    Entity * enemy2 = this->entityBuilder->createEnemy(500,150);
    this->entityMap->operator[](enemy2->getId()) = enemy2;

    Entity * enemy3 = this->entityBuilder->createEnemy(650,150);
    this->entityMap->operator[](enemy3->getId()) = enemy3;

    Entity * enemy4 = this->entityBuilder->createEnemy(400,300);
    this->entityMap->operator[](enemy4->getId()) = enemy4;

    Entity * enemy5 = this->entityBuilder->createEnemy(600,300);
    this->entityMap->operator[](enemy5->getId()) = enemy5;
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
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return;
                } else {
                    inputHandler->handleEvent(event);
                }
            } else {
                inputHandler->handleEvent(event);
            }
        }

        aiHandler->handleAiCommands();
        aiHandler->update(dt);
        inputHandler->update(dt);
        collisionHandler->handleCollisions();
        soundHandler->handleSFX(dt);

        SDL_RenderClear(this->renderer);
        SDL_RenderCopy(this->renderer, this->texture, NULL,&this->backgroundRect);
        drawer->draw(this->entityMap, dt);
        SDL_RenderPresent(this->renderer);
    }
}

void PlayState::cleanup() {
    if(this->texture!=NULL){
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
}
