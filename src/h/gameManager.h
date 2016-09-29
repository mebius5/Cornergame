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
#include "entityBuilder.h"
#include "inputHandler.h"
#include "soundHandler.h"
#include "aiHandler.h"
#include "collisionHandler.h"
#include "state.h"


class GameManager {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

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
