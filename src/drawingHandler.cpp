#include "drawingHandler.h"

DrawingHandler::DrawingHandler(std::map<int, ArtComponent*>& componentMap,
                               SDL_Renderer* renderer) :
    componentMap(componentMap),
    renderer(renderer) {
}

void DrawingHandler::draw(int dt) {
    SDL_RenderClear(this->renderer);
    std::map<int, ArtComponent*>::const_iterator it;
    for (int i = 0; i <= ArtComponent::MAXLAYER; i++) {
        for (it = this->componentMap.begin(); it != this->componentMap.end(); ++it) {
            ArtComponent* artComp = it->second;
            Entity* entity = artComp->entity;
            if (artComp->layer == i) {
                SDL_Rect rect = { (int) entity->x,
                                  (int) entity->y,
                                  entity->width,
                                  entity->height };
                SDL_RenderCopy(this->renderer, artComp->getNextTexture(dt),
                               artComp->getNextSrcRect(dt), &rect);
            }
        }
    }
    SDL_RenderPresent(this->renderer);
}
