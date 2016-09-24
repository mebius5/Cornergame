#include "drawingHandler.h"

DrawingHandler::DrawingHandler(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void DrawingHandler::draw(std::map<int, Entity*>& entityMap) {\
    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        Entity* entity = it->second;
        if (entity->art && entity->location) {
            SDL_Rect rect = {entity->location->x, entity->location->y,
                             entity->location->width, entity->location->height};
            SDL_RenderCopy(this->renderer, entity->art->texture, NULL, &rect);
        }
    }
}
