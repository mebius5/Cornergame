#ifndef CORNERGAME_DRAWING_HANDLER_H
#define CORNERGAME_DRAWING_HANDLER_H

#include <map>
#include "entity.h"

class DrawingHandler {
private:
    SDL_Renderer* renderer;
    std::map<int, Entity*>& entityMap;
public:
    DrawingHandler(SDL_Renderer* renderer, std::map<int, Entity*>& entityMap);
    void draw(int dt);
};

#endif
