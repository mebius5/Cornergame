#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <math.h>
#include <cstdio>
#include "gameManager.h"
#include "entity.h"
#include "system.h"

#define TWO_PI 2 * M_PI
#define RAD_TO_DEG 180 / M_PI

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
    commandList = new std::list<Command>();
    entityList = new std::list<Entity>();
}

// Setup the instance of SDL2
void GameManager::setup() {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("Unable to initialize SDL:  %s\n", SDL_GetError());
        return;
    }

    // Initialize font
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    // Initialize image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_img could not initialize! SDL_img Error: %s\n", IMG_GetError());
        return;
    }

    // Initialize Mixer
    if (Mix_Init(MIX_INIT_MOD)) {
        printf("The mixer failed to initialize!\n");
        return;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        printf("The mixer failed to initialize!\n");
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
        printf("Unable to initialize renderer:  %s\n", SDL_GetError());
        return;
    }
}

// Load the necessary assets
void GameManager::load() {
    // Load music
    this->music = Mix_LoadMUS("resources/abstract_tracking.xm");
    if (!this->music) {
        printf("Unable to load music:  %s\n", SDL_GetError());
    }

    // Load image
    SDL_Surface* loadedImage = IMG_Load("resources/jhu_logo.png");
    SDL_Surface* finalImage = NULL;
    if (loadedImage == NULL) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        return;
    } else {
        finalImage = SDL_ConvertSurface(loadedImage, loadedImage->format, 0);
        if (finalImage == NULL) {
            printf("Unable to optimize image! SDL Error: %s\n", SDL_GetError());
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
    SDL_Rect textureRect = centeredRect(this->width, this->height,
                                        this->texWidth, this->texHeight);

    Hero hero(this->renderer, 0, 0, 0, 0);

    this->entityList->push_back(hero);

    Drawer drawer(this->renderer);

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
            }
        }

        SDL_SetRenderDrawColor( this->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(this->renderer);

        drawer.draw(this->entityList);

        SDL_RenderPresent(this->renderer);
    }
}

int main(void) {
    GameManager manager;
    manager.setup();
    manager.load();
    manager.run();
    manager.cleanup();
}
