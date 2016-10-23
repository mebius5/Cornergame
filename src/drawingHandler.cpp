#include "drawingHandler.h"

DrawingHandler::DrawingHandler(std::vector<ArtComponent*>& componentList,
                               SDL_Renderer* renderer, int windowW, int windowH) :
    componentList(componentList),
    renderer(renderer),
    camera(renderer, componentList, windowW, windowH),
    shiftCount(0){

}

void DrawingHandler::initializeCamera(int levelW, int levelH) {
    this->camera.setLevelWH(levelW, levelH);
}

void DrawingHandler::draw(int dt) {
    SDL_RenderClear(this->renderer);
    std::vector<ArtComponent*>::iterator it;

    for (int i = 0; i <= ArtComponent::MAXLAYER; i++) {
        for (it = this->componentList.begin(); it != this->componentList.end(); ) {
            if (!(*it)->isValid()) {        // remove invalid components
                *it = this->componentList.back();
                this->componentList.pop_back();
                continue;
            }

            ArtComponent* artComp = *it;
            camera.draw(dt, artComp);
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

void DrawingHandler::resetCamera(int windowW, int windowH){
    camera.resetCamera(windowW, windowH);
}