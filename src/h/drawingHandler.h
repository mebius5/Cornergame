#ifndef CORNERGAME_DRAWING_HANDLER_H
#define CORNERGAME_DRAWING_HANDLER_H

#include <array>
#include <vector>
#include "entity.h"
#include "camera.h"

class DrawingHandler {
private:
    std::vector<Command*>& commandList;
    std::vector<ArtComponent*>& componentList;
    std::array<int, NLAYERS>& layerIndices;
    SDL_Renderer* renderer;
    Camera camera;
    int shiftCount;
    int windowW;
    void removeInvalidComponents();
public:
    DrawingHandler(std::vector<Command*>& commandList,
                   std::vector<ArtComponent*>& componentList,
                   std::array<int, NLAYERS>& layerIndices,
                   std::vector<BackgroundArtComponent*>& bgComponents,
                   SDL_Renderer* renderer, int windowW, int windowH);
    void draw(int dt);
    void shift(int dt);
    void resetCamera(int minX, int minY, int maxX, int maxY);
    void initializeCamera(int levelW, int levelH, bool previewOn);
    bool previewLevel(int dt);      // returns whether preview is still active.
    void checkCameraShakes();
};

#endif
