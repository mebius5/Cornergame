#include "drawingHandler.h"

DrawingHandler::DrawingHandler(SDL_Renderer* r, std::map<int, Entity*>& map) :
    renderer(r),
    entityMap(map) {
}

void DrawingHandler::draw(int dt) {
    std::map<int, Entity*>::const_iterator it;
    for (it = this->entityMap.begin(); it != this->entityMap.end(); ++it) {
        Entity* entity = it->second;
        if (entity->art) {
            SDL_Rect rect = { (int) entity->x,
                              (int) entity->y,
                              entity->width,
                              entity->height };
            SDL_RenderCopy(this->renderer, entity->art->getNextTexture(dt),
                           NULL, &rect);
        }
    }
}
