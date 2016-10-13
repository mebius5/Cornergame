#ifndef CORNERGAME_CAMERA_H
#define CORNERGAME_CAMERA_H

#include "artComponent.h"

class Camera{
private:
    SDL_Renderer * renderer;
    int minX;
    int minY;
    int maxX;
    int maxY;
public:
    Camera(SDL_Renderer * renderer, int windowW, int windowH);
    ~Camera();
    void draw(int dt, ArtComponent * artComponent);
    void shift(int dx, int dy);
    void resetCamera(int windowW, int windowH);
};

#endif //CORNERGAME_CAMERA_H
