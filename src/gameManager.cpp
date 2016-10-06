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

// Cleanup the instance of SDL2
void GameManager::cleanup() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    this->renderer = NULL;
    this->window = NULL;
}

// Run the actual program
void GameManager::run() {
    // Initialization
    std::list<Command*> commandList;
    Component::setCommandList(&commandList);

    EntityManager entityMgr(this->renderer);
    DrawingHandler drawingHandler(entityMgr.artComponents, this->renderer);
    InputHandler inputHandler(entityMgr.inputComponents, commandList);
    AiHandler aiHandler(entityMgr.aiComponents, commandList);
    CollisionHandler collisionHandler(entityMgr.collisionComponents,
                                      commandList, this->width, this->height);
    SoundHandler soundHandler(commandList);
    ControlHandler controlHandler(commandList);

    StartState startState(this->width, this->height, entityMgr, commandList,
                          this->renderer, drawingHandler, inputHandler,
                          soundHandler, controlHandler);

    MenuState menuState(this->width, this->height, entityMgr, commandList,
                        this->renderer, drawingHandler, inputHandler,
                        soundHandler, controlHandler);

    PlayState playState(this->width, this->height, entityMgr, commandList,
                        this->renderer, drawingHandler, inputHandler,
                        soundHandler, controlHandler, aiHandler,
                        collisionHandler);

    HighscoreState highscoreState(this->width, this->height, entityMgr,
                                  commandList, this->renderer, drawingHandler,
                                  inputHandler, soundHandler, controlHandler);

    // State loop
    State* currentState = &startState;
    StateEnum nextState;

    do {
        currentState->begin();
        nextState = currentState->run();
        currentState->cleanup();

        switch (nextState) {
        case STATE_PLAY:
            currentState = &playState;
            break;
        case STATE_HIGHSCORE:
            currentState = &highscoreState;
            break;
        case STATE_MENU:
            currentState = &menuState;
            break;
        default:
            break;
        }
    } while (nextState != STATE_QUIT);

    // Cleanup Entities and Commands
    entityMgr.clear();
    commandList.clear();
}

int main(void) {
    GameManager manager;
    manager.setup();
    manager.run();
    manager.cleanup();
}
