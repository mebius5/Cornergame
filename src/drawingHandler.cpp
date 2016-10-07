#include "drawingHandler.h"

DrawingHandler::DrawingHandler(std::vector<ArtComponent*>& componentList,
                               SDL_Renderer* renderer) :
    componentList(componentList),
    renderer(renderer) {
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
            Entity* entity = artComp->entity;
            if (artComp->layer == i) {
                SDL_Rect rect = { (int) entity->x,
                                  (int) entity->y,
                                  entity->width,
                                  entity->height };
                SDL_RenderCopy(this->renderer, artComp->getNextTexture(dt),
                               artComp->getNextSrcRect(dt), &rect);
            }
            ++it;
        }
    }
    SDL_RenderPresent(this->renderer);
}
