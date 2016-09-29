#define TWO_PI 2 * M_PI
#define RAD_TO_DEG 180 / M_PI

#include "gameManager.h"

/* gameManager.cpp
 * Cornerstone <GAME NAME>
 * This class initializes and closes SDL resources, and manages the game loop.
 */


GameManager::GameManager() :
        title("<GAME NAME>"),
        width(1280),
        height(720) {

    srand(time(NULL));
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

    // Initialize mixer
    if (Mix_Init(MIX_INIT_MOD)) {
        std::cerr << "The mixer failed to initialize!" << std::endl;
        return;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        std::cerr << "The mixer failed to initialize!" << std::endl;
        return;
    }
}

// Load the necessary assets
void GameManager::load() {

    // Load fonts
    this->font = TTF_OpenFont("resources/CaesarDressing-Regular.ttf", 30);
}

// Cleanup the instance of SDL2
void GameManager::cleanup() {
    TTF_CloseFont(this->font);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    //Set free pointers
    this->renderer = NULL;
    this->window = NULL;
}

// Run the actual program
void GameManager::run() {
    bool running = true;
    float lastTime = 0;
    float time = 0;

    SDL_Event event;
    std::list<Command *> commandList;
    std::map<int, Entity *> entityMap;

    DrawingHandler drawer(this->renderer);
    EntityBuilder entityBuilder(this->renderer);
    InputHandler inputHandler(entityMap, commandList);
    AiHandler aiHandler(entityMap, commandList);
    LocationHandler locationHandler(commandList);
    CollisionHandler collisionHandler(entityMap, commandList,
                                      this->width, this->height);
    SoundHandler soundHandler(commandList);

    State * currentState;

    //Initialize play state
    PlayState playState(this->renderer, this->width, this->height,
                        &commandList, &entityMap, &drawer,
                        &entityBuilder, &inputHandler,
                        &locationHandler, &aiHandler,
                        &collisionHandler, &soundHandler);

    currentState = & playState;

    while (running) {


        currentState->begin();

        while (running) {
            int currentTime = SDL_GetTicks();
            int dt = currentTime - lastTime;
            time += dt / 1000.0;
            lastTime = currentTime;

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYUP) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                }
            }

            currentState->iterate(currentTime);
        }

        currentState->cleanup();
    }

    // Release memory for Entities and Commands
    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        delete it->second;      // delete Entity
    }
    entityMap.clear();

    commandList.clear();
}

int main(void) {
    GameManager manager;
    manager.setup();
    manager.load();
    manager.run();
    manager.cleanup();
}
