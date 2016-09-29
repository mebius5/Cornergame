#include <state.h>

int PlayState::center(int large, int small) {
    return (large / 2 - small / 2);
}

SDL_Rect PlayState::centeredRect(int largeW, int largeH, int smallW, int smallH) {
    SDL_Rect rect = {
            center(largeW, smallW), center(largeH, smallH),
            smallW, smallH
    };
    return rect;
}

PlayState::PlayState(SDL_Renderer * renderer, int windowW, int windowH, std::list<Command*> * commandList,
                     std::map<int, Entity*> * entityMap, DrawingHandler * drawingHandler,
                     EntityBuilder * entityBuilder, InputHandler * inputHandler, LocationHandler * locationHandler, AiHandler * aiHandler,
                     CollisionHandler * collisionHandler, SoundHandler * soundHandler) {
    this->renderer = renderer;
    this->windowW = windowW;
    this->windowH = windowH;
    this->commandList = commandList;
    this->entityMap = entityMap;
    this->drawer = drawingHandler;
    this->entityBuilder = entityBuilder;
    this->inputHandler = inputHandler;
    this->locationHandler = locationHandler;
    this->aiHandler = aiHandler;
    this->collisionHandler = collisionHandler;
    this->soundHandler = soundHandler;
}


PlayState::~PlayState() {
    SDL_DestroyTexture(this->texture);
    this->drawer = NULL;
    this->entityBuilder = NULL;
    this->inputHandler = NULL;
    this->locationHandler = NULL;
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

void PlayState::iterate(int dTime) {
    inputHandler->pollKeys();
    aiHandler->handleAiCommands();
    aiHandler->handleAi(dTime);
    locationHandler->handleLocationCommands(dTime);
    collisionHandler->handleCollision();
    soundHandler->handleSFX(dTime);

    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture, NULL,&this->backgroundRect);
    drawer->draw(this->entityMap,dTime);
    SDL_RenderPresent(this->renderer);
}

void PlayState::cleanup() {
    SDL_DestroyTexture(this->texture);
    this->drawer = NULL;
    this->entityBuilder = NULL;
    this->inputHandler = NULL;
    this->locationHandler = NULL;
    this->aiHandler = NULL;
    this->collisionHandler = NULL;
    this->soundHandler = NULL;
}