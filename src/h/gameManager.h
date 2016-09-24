#ifndef CORNERGAME_GAME_MANAGER_H
#define CORNERGAME_GAME_MANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <math.h>
#include <list>
#include <map>
#include <iostream>
#include "command.h"
#include "entity.h"
#include "drawingHandler.h"
#include "entityHandler.h"

#define TWOPI 2 * M_PI
#define RAD_TO_DEG 180 / M_PI

class GameManager {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Mix_Music* music;

    SDL_Texture* texture;     // background texture
    int texWidth;
    int texHeight;
    TTF_Font* font;

    const char* title;
    const int width;
    const int height;

public:
    GameManager();
    void setup();
    void load();
    void run();
    void cleanup();
};

#endif //CORNERGAME_GAME_MANAGER_H
