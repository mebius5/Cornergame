#ifndef CORNERGAME_DRAWING_HANDLER_H
#define CORNERGAME_DRAWING_HANDLER_H

#include <list>
#include "entity.h"

class DrawingHandler {
private:
    SDL_Renderer* renderer;
public:
    DrawingHandler(SDL_Renderer* renderer);
    void draw(std::list<Entity*>& entityList);
};

#endif //CORNERGAME_DRAWING_HANDLER_H
