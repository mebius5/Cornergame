#include "gameManager.h"

/* gameManager.cpp
 * Cornerstone <GAME NAME>
 * This class initializes and closes SDL resources, and manages the game loop.
 */

GameManager::GameManager() :
    title("<GAME NAME>"),
    width(1024),
    height(704),
    currentLevel(1),
    maxLevel(4) {
    srand((unsigned int) time(NULL));
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
    this->renderer = SDL_CreateRenderer(this->window, -1, (Uint32) rendererFlags);

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
    std::vector<Command*> commandList;
    Component::setCommandList(&commandList);

    EntityManager entityMgr(this->renderer, commandList, width);
    DrawingHandler drawingHandler(commandList, entityMgr.artComponents, this->renderer, width, height);
    InputHandler inputHandler(entityMgr.inputComponents, commandList);
    AiHandler aiHandler(entityMgr.aiComponents);
    CollisionHandler collisionHandler(entityMgr.dynamicCollisionComponents,
                                      entityMgr.staticCollisionComponents);
    SoundHandler soundHandler(commandList);
    ControlHandler controlHandler(commandList);
    ScoreHandler scoreHandler(entityMgr.scoreComponents);
    PhysicsHandler physicsHandler(entityMgr.physicsComponents);
    PowerUpHandler powerUpHandler(entityMgr.powerUpComponents);
    TimeHandler timeHandler(commandList);

    StartState startState(this->width, this->height, entityMgr, commandList,
                          this->renderer, drawingHandler, inputHandler,
                          soundHandler, controlHandler, collisionHandler, physicsHandler);
    MenuState menuState(this->width, this->height, entityMgr, commandList,
                        this->renderer, drawingHandler, inputHandler,
                        soundHandler, controlHandler);
    HighscoreState highscoreState(this->width, this->height, entityMgr,
                                  commandList, this->renderer, drawingHandler,
                                  inputHandler, soundHandler, controlHandler);
    ResultsState resultsState(this->width, this->height, entityMgr,
                              commandList, this->renderer, drawingHandler,
                              inputHandler, soundHandler, controlHandler);

    LevelTransitState levelTransitState(this->width, this->height, entityMgr,
                              commandList, this->renderer, drawingHandler,
                              inputHandler, soundHandler, controlHandler);

    PlayState playState(this->width, this->height, entityMgr, commandList,
                        this->renderer, drawingHandler, inputHandler,
                        soundHandler, controlHandler, aiHandler,
                        collisionHandler, scoreHandler, physicsHandler,
                        powerUpHandler, timeHandler, resultsState, highscoreState);

    TutorialState tutorialState(this->width, this->height, entityMgr, commandList,
                        this->renderer, drawingHandler, inputHandler,
                        soundHandler, controlHandler, aiHandler,
                        collisionHandler, scoreHandler, physicsHandler,
                        powerUpHandler);

    // Load music resources
    soundHandler.loadMusic("music/mega_destruction_titlescreen.xm", MUSIC_START);
    soundHandler.loadMusic("music/a_winter_kiss_menu.xm", MUSIC_MENU);
    soundHandler.loadMusic("music/cabin_fever_playscreen.xm", MUSIC_PLAY);
    soundHandler.loadMusic("music/ambient_starfield_highscore.xm", MUSIC_HIGHSCORE);
    soundHandler.loadSfx("resources/ouch_hero.aiff", SFX_ALERT);
    soundHandler.loadSfx("resources/ammo.wav", SFX_AMMO);
    soundHandler.loadSfx("resources/armor.wav", SFX_ARMOR);
    soundHandler.loadSfx("resources/drink.wav", SFX_DRINK);
    soundHandler.loadSfx("resources/jump.wav", SFX_JUMP);
    soundHandler.loadSfx("resources/land.aiff", SFX_LAND);
    soundHandler.loadSfx("resources/ouch_enemy.aiff", SFX_ENEMY);
    soundHandler.loadSfx("resources/rumble.aiff", SFX_RUMBLE);
    soundHandler.loadSfx("resources/running.aiff", SFX_RUNNING);
    soundHandler.loadSfx("resources/scrape.aiff", SFX_SCRAPE);
    soundHandler.loadSfx("resources/woosh.aiff", SFX_WOOSH);
    soundHandler.loadSfx("resources/jump.wav", SFX_BOUNCE);

    // State loop
    State* currentState = &startState;
    StateEnum nextState;

    do {
        currentState->begin(this->currentLevel);
        nextState = currentState->run();
        currentState->cleanup(nextState);

        switch (nextState) {
            case STATE_PLAY:
                currentState = &playState;
                break;
            case STATE_LEVEL_TRANSIT:
                currentState = &levelTransitState;
                if (this->currentLevel > maxLevel) {
                    currentState = &menuState;
                    this->currentLevel = 1;
                }
                break;
            case STATE_TUTORIAL:
                currentState = &tutorialState;
                this->currentLevel=1;
                break;
            case STATE_HIGHSCORE:
                currentState = &highscoreState;
                this->currentLevel=1;
                break;
            case STATE_MENU:
                currentState = &menuState;
                this->currentLevel=1;
                break;
            case STATE_RESULTS:
                currentState = &resultsState;
                this->currentLevel++;
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
