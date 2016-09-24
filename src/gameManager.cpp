
#define TWO_PI 2 * M_PI
#define RAD_TO_DEG 180 / M_PI


#include "gameManager.h"

/* gameManager.cpp
 * Cornerstone <GAME NAME>
 * This class initializes and closes SDL resources, and manages the game loop.
 */

double radToDeg(float radians) {
    return RAD_TO_DEG * radians;
}

int center(int large, int small) {
    return (large / 2 - small / 2);
}

SDL_Rect centeredRect(int largeW, int largeH, int smallW, int smallH) {
    SDL_Rect rect = {
            center(largeW, smallW), center(largeH, smallH),
            smallW, smallH
    };
    return rect;
}

GameManager::GameManager() : title("<GAME NAME>"), width(800), height(600) {

}

// Setup the instance of SDL2
void GameManager::setup() {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Unable to initialize SDL: "
                  << SDL_GetError() << std::endl;
        return;
    }

    // Initialize font
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: "
                  << TTF_GetError() << std::endl;
        return;
    }

    // Initialize image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_img could not initialize! SDL_img Error: "
                  << IMG_GetError() << std::endl;
        return;
    }

    // Initialize Mixer
    if (Mix_Init(MIX_INIT_MOD)) {
        std::cerr << "The mixer failed to initialize!" << std::endl;
        return;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        std::cerr << "The mixer failed to initialize!" << std::endl;
        return;
    }

    // Initialize window
    this->window = SDL_CreateWindow(
            this->title,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            this->width, this->height,
            SDL_WINDOW_SHOWN
    );

    if (!this->window) {
        printf("Unable to initialize window:  %s\n", SDL_GetError());
        return;
    }

    // Initialize renderer
    int rendererFlags = SDL_RENDERER_ACCELERATED;
    this->renderer = SDL_CreateRenderer(this->window, -1, rendererFlags);

    if (!this->renderer) {
        std::cerr << "Unable to initialize renderer: "
                  << SDL_GetError() << std::endl;
        return;
    }
}

// Load the necessary assets
void GameManager::load() {
    // Load music
    this->music = Mix_LoadMUS("resources/abstract_tracking.xm");
    if (!this->music) {
        std::cerr << "Unable to load music: " << SDL_GetError() << std::endl;
    }

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
    this->texWidth = finalImage->w;
    this->texHeight = finalImage->h;
    this->texture = SDL_CreateTextureFromSurface(this->renderer, finalImage);
    SDL_FreeSurface(finalImage);

    // Load fonts
    this->font = TTF_OpenFont("resources/CaesarDressing-Regular.ttf", 30);
}

// Cleanup the instance of SDL2
void GameManager::cleanup() {
    TTF_CloseFont(this->font);
    SDL_DestroyTexture(this->texture);
    Mix_FreeMusic(this->music);
    Mix_CloseAudio();
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();

    //Set free pointers
    this->texture = NULL;
    this->music = NULL;
    this->renderer = NULL;
    this->window = NULL;
}

// Run the actual program
void GameManager::run() {
    bool running = true;
    float lastTime = 0;
    float time = 0;

    SDL_Event event;
    Mix_PlayMusic(this->music, -1);

    std::list<Command * > commandList;
    std::map<int, Entity*> entityMap;
    DrawingHandler drawer(this->renderer);
    EntityHandler entityHandler(this->renderer);
    InputHandler inputHandler(entityMap, commandList);
    MovementHandler movementHandler(entityMap, commandList);
    LocationHandler locationHandler;
    CollisionHandler collisionHandler(entityMap, commandList, this->width, this->height);

    SDL_Rect backgroundRect = centeredRect(this->width, this->height,
                                           this->texWidth, this->texHeight);

    // Create hero entity
    Entity* hero = entityHandler.createHero(100, 100);
    entityMap[hero->getId()] = hero;


    //Create enemy entities
    Entity * enemy1 = entityHandler.createEnemy(350,150);
    entityMap[enemy1->getId()] = enemy1;

    Entity * enemy2 = entityHandler.createEnemy(500,150);
    entityMap[enemy2->getId()] = enemy2;

    Entity * enemy3 = entityHandler.createEnemy(650,150);
    entityMap[enemy3->getId()] = enemy3;

    Entity * enemy4 = entityHandler.createEnemy(400,300);
    entityMap[enemy4->getId()] = enemy4;

    Entity * enemy5 = entityHandler.createEnemy(600,300);
    entityMap[enemy5->getId()] = enemy5;

    while (running) {
        int currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        time += dt/1000.0;
        lastTime = currentTime;

        if (time > TWO_PI) {
            time -= TWO_PI;
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_ESCAPE ||
                    event.key.keysym.sym == SDLK_q) {
                    running = false;
                }
            } else if (event.type == SDL_KEYDOWN){
                    inputHandler.handleKeyDown(event);
            }
        }

        SDL_RenderClear(this->renderer);
        SDL_RenderCopyEx(this->renderer, this->texture, NULL, &backgroundRect,
                         radToDeg(sin(time)), NULL, SDL_FLIP_NONE);

        //movementHandler.handleMovement();

        locationHandler.handleLocationCommands(commandList);

        collisionHandler.handleCollision();

        drawer.draw(entityMap);

        SDL_RenderPresent(this->renderer);
    }


    // Release memory for Entities
    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        delete it->second;      // delete Entity
    }
    entityMap.clear();


    // Release memory for Commands
    std::list<Command *>::const_iterator cIt;
    for(cIt = commandList.begin(); cIt != commandList.end(); ++cIt){
        delete *cIt;
    }
    commandList.clear();
}

int main(void) {
    GameManager manager;
    manager.setup();
    manager.load();
    manager.run();
    manager.cleanup();
}
