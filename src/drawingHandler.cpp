#include "drawingHandler.h"

DrawingHandler::DrawingHandler(std::vector<Command*>& commandList,
                               std::vector<ArtComponent*>& componentList,
                               std::array<int, NLAYERS>& layerIndices,
                               std::vector<BackgroundArtComponent*>& bgComponents,
                               SDL_Renderer* renderer, int windowW, int windowH) :
    commandList(commandList),
    componentList(componentList),
    layerIndices(layerIndices),
    renderer(renderer),
    camera(renderer, commandList, componentList, bgComponents, windowW, windowH),
    shiftCount(0),
    windowW(windowW) {
}

void DrawingHandler::initializeCamera(int levelW, int levelH, bool previewOn) {
    this->camera.initializeCamera(levelW, levelH, previewOn);
}

void DrawingHandler::removeInvalidComponents() {
    std::vector<ArtComponent*>::iterator it;
    for (it = this->componentList.begin(); it != this->componentList.end(); ) {
        if (!(*it)->isValid()) {        // remove invalid components
            int layer = (*it)->layer;
            *it = this->componentList[this->layerIndices[layer]];
            this->layerIndices[layer]=this->layerIndices[layer]-1;
            for (int i = layer; i < NLAYERS-1; i++){
                this->componentList[this->layerIndices[i]+1] = this->componentList[this->layerIndices[i+1]];
                this->layerIndices[i+1]=this->layerIndices[i+1]-1;
            }
            this->componentList.pop_back();
            continue;
        }
        ++it;
    }
}

void DrawingHandler::draw(int dt) {
    SDL_RenderClear(this->renderer);
    this->camera.updateShake(dt);
    this->removeInvalidComponents();

    std::vector<ArtComponent*>::iterator it;
    for (it = this->componentList.begin(); it != this->componentList.end(); ++it) {
        ArtComponent* artComp = *it;
        artComp->updateLocation();
        if (artComp->isVisible)
            camera.draw(dt, artComp);
    }

    for (it = this->componentList.begin(); it != this->componentList.end(); ++it) {
        ArtComponent* artComp = *it;
        artComp->updateLocation();
        if (artComp->isVisible)
            camera.drawLighting(dt, artComp);
    }

    SDL_RenderPresent(this->renderer);
}

void DrawingHandler::shift(int dt) {
    shiftCount+=dt;

    if(shiftCount>=10){
        camera.shift(shiftCount/10,0);
        shiftCount=shiftCount%10;
    }
}

void DrawingHandler::resetCamera(int minX, int minY, int maxX, int maxY) {
    camera.resetCamera(minX, minY, maxX, maxY);
}

bool DrawingHandler::previewLevel(int dt) {
    shiftCount+=dt;

    if (shiftCount >= 2) {
        if (camera.minY > 0) {
            camera.shift(0, -(shiftCount/4+1));
        } else if (this->camera.minX > this->windowW) {
            camera.shift(-(shiftCount/4+1), 0);
        } else {
            return false;
        }
        shiftCount = 0;
    }

    return true;
}

void DrawingHandler::checkCameraShakes() {
    std::vector<Command*>::iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end();) {
        if (dynamic_cast<CameraShakeCommand*>(*it)) {
            *it = this->commandList.back();
            this->commandList.pop_back();
            this->camera.startShake();
        } else {
            ++it;
        }
    }
}
