#include "drawingHandler.h"

DrawingHandler::DrawingHandler(SDL_Renderer* renderer) :
    renderer(renderer) {
}

void DrawingHandler::draw(std::map<int, Entity*>& entityMap, int dt) {\
    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
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
