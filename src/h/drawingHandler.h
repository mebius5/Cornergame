#ifndef CORNERGAME_DRAWING_HANDLER_H
#define CORNERGAME_DRAWING_HANDLER_H

#include <vector>
#include "entity.h"

class DrawingHandler {
private:
    std::vector<ArtComponent*>& componentList;
    SDL_Renderer* renderer;
public:
    DrawingHandler(std::vector<ArtComponent*>& componentList,
                   SDL_Renderer* renderer);
    void draw(int dt);
};

#endif
