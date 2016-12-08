#ifndef CORNERGAME_CAMERA_H
#define CORNERGAME_CAMERA_H

#include "artComponent.h"

class Camera {
private:
    SDL_Renderer* renderer;
    std::vector<Command*>& commandList;
    std::vector<ArtComponent*>& componentList;
    std::vector<BackgroundArtComponent*>& bgComponents;
    LoopLevelCommand* loopLevelCommand;
    Command* rumbleCommand;
    int levelW;
    int levelH;
    bool previewOn;
    int offsetX;
    int offsetY;
    int shakeTime;
    int maxShakeTime;
    int shakeDist;
    int windowW;
    int windowH;
public:
    float minX;
    float minY;
    float maxX;
    float maxY;

    Camera(SDL_Renderer* renderer, std::vector<Command*>& commandList,
           std::vector<ArtComponent*>& componentList,
           std::vector<BackgroundArtComponent*>& bgComponents,
           int windowW, int windowH);
    ~Camera();
    void startShake();
    void updateShake(int dt);
    void draw(int dt, ArtComponent *artComponent);
    void drawLighting(int dt, ArtComponent * artComponent);
    void shift(float dx, float dy);
    void resetCamera(int minX, int minY, int maxX, int maxY);
    void initializeCamera(int levelW, int levelH, bool previewOn);
    void detectBorderCollision(Entity *entity, int dt);
};

#endif
