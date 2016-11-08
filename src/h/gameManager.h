#ifndef CORNERGAME_GAME_MANAGER_H
#define CORNERGAME_GAME_MANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <map>
#include <iostream>
#include "command.h"
#include "entity.h"
#include "enums.h"
#include "drawingHandler.h"
#include "entityManager.h"
#include "inputHandler.h"
#include "soundHandler.h"
#include "aiHandler.h"
#include "collisionHandler.h"
#include "controlHandler.h"
#include "physicsHandler.h"
#include "powerUpHandler.h"
#include "scoreHandler.h"
#include "state.h"

class GameManager {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    const char* title;
    const int width;
    const int height;

    int currentLevel;
    int maxLevel;

public:
    GameManager();
    void setup();
    void run();
    void cleanup();
};

#endif
