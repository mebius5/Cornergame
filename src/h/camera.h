#ifndef CORNERGAME_CAMERA_H
#define CORNERGAME_CAMERA_H

#include "artComponent.h"

class Camera{
private:
    SDL_Renderer * renderer;
    std::vector<ArtComponent*>& componentList;
    int minX;
    int minY;
    int maxX;
    int maxY;
    int levelW;
    int levelH;
public:

    Camera(SDL_Renderer * renderer, std::vector<ArtComponent*>& componentList, int windowW, int windowH);
    ~Camera();
    void draw(int dt, ArtComponent * artComponent);
    void shift(int dx, int dy);
    void resetCamera(int windowW, int windowH);
    void setLevelWH(int levelW, int levelH);
};

#endif //CORNERGAME_CAMERA_H
