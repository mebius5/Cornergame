#include "drawingHandler.h"

DrawingHandler::DrawingHandler(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void DrawingHandler::draw(std::list<Entity*>& entityList) {\
    std::list<Entity*>::const_iterator it;
    for (it = entityList.begin(); it != entityList.end(); it++) {
        Entity* entity = *it;
        if (entity->art && entity->location) {
            SDL_Rect rect = {entity->location->x, entity->location->y,
                             entity->location->width, entity->location->height};
            SDL_RenderCopy(this->renderer, entity->art->texture, NULL, &rect);
        }
    }
}
