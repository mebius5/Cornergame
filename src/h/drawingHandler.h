#ifndef CORNERGAME_DRAWING_HANDLER_H
#define CORNERGAME_DRAWING_HANDLER_H

#include <map>
#include "entity.h"

class DrawingHandler {
private:
    SDL_Renderer* renderer;
public:
    DrawingHandler(SDL_Renderer* renderer);
    void draw(std::map<int, Entity*>& entityMap, int dTime);
};

#endif
