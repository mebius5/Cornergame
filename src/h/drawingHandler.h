#ifndef CORNERGAME_DRAWING_HANDLER_H
#define CORNERGAME_DRAWING_HANDLER_H

#include <vector>
#include "entity.h"
#include "camera.h"

class DrawingHandler {
private:
    std::vector<ArtComponent*>& componentList;
    SDL_Renderer* renderer;
    Camera camera;
public:
    DrawingHandler(std::vector<ArtComponent*>& componentList,
                   SDL_Renderer* renderer, int windowW, int windowH);
    void draw(int dt);
};

#endif
