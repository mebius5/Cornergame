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
    void detectBorderCollision(Entity *entity, int dt);
    void borderBoundX(Entity* entity, float boundValue);
    void borderBoundY(Entity* entity, float boundValue);
};

#endif //CORNERGAME_CAMERA_H
