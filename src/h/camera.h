#ifndef CORNERGAME_CAMERA_H
#define CORNERGAME_CAMERA_H

#include "artComponent.h"

class Camera{
private:
    SDL_Renderer * renderer;
    std::vector<ArtComponent*>& componentList;
    int levelW;
    int levelH;
    bool previewOn;
public:
    int minX;
    int minY;
    int maxX;
    int maxY;
    int offsetX;
    int offsetY;
    int shakeTime;
    int maxShakeTime;
    int shakeDist;

    Camera(SDL_Renderer * renderer, std::vector<ArtComponent*>& componentList, int windowW, int windowH);
    ~Camera();
    void startShake();
    void updateShake(int dt);
    void draw(int dt, ArtComponent *artComponent);
    void shift(int dx, int dy);
    void resetCamera(int minX, int minY, int maxX, int maxY);
    void initializeCamera(int levelW, int levelH, bool previewOn);
    void detectBorderCollision(Entity *entity, int dt);
    void borderBoundX(Entity* entity, float boundValue);
    void borderBoundY(Entity* entity, float boundValue);
};

#endif //CORNERGAME_CAMERA_H
