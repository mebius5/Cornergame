#include "drawingHandler.h"

DrawingHandler::DrawingHandler(std::vector<Command*>& commandList,
                               std::vector<ArtComponent*>& componentList,
                               SDL_Renderer* renderer, int windowW, int windowH) :
    commandList(commandList),
    componentList(componentList),
    renderer(renderer),
    camera(renderer, commandList, componentList, windowW, windowH),
    shiftCount(0){

}

void DrawingHandler::initializeCamera(int levelW, int levelH, bool previewOn) {
    this->camera.initializeCamera(levelW, levelH, previewOn);
}

void DrawingHandler::draw(int dt) {
    SDL_RenderClear(this->renderer);
    std::vector<ArtComponent*>::iterator it;

    // shake the camera
    camera.updateShake(dt);

    for (int i = 0; i <= ArtComponent::MAXLAYER; i++) {
        for (it = this->componentList.begin(); it != this->componentList.end(); ) {
            if (!(*it)->isValid()) {        // remove invalid components
                *it = this->componentList.back();
                this->componentList.pop_back();
                continue;
            }

            ArtComponent* artComp = *it;
            if(artComp->layer==i && artComp->isVisible){
                camera.draw(dt, artComp);
            }
            ++it;
        }
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

    if(shiftCount>=2){
        if(camera.minX>0){
                camera.shift(-(shiftCount/4+1), 0);
        }
        if(camera.minX<=0&&camera.minY>0){
                camera.shift(0, -(shiftCount/4+1));
        }
        shiftCount=0;
    }

    return !(camera.minX <= 0 && camera.minY <= 0);

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
