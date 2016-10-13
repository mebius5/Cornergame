#include "drawingHandler.h"

DrawingHandler::DrawingHandler(std::vector<ArtComponent*>& componentList,
                               SDL_Renderer* renderer, int windowW, int windowH) :
    componentList(componentList),
    renderer(renderer),
    camera(renderer, windowW, windowH) {

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
