#include <list>
#include "entity.h"
#include "system.h"


Drawer::Drawer(SDL_Renderer * renderer) {
    this->renderer = renderer;
}

void Drawer::draw(std::list <Entity> *entityList) {
    std::list<Entity>::const_iterator iterator;
    for(iterator = entityList->begin(); iterator != entityList->end(); ++iterator){
        Entity entity = * iterator;
        if(entity.texture){
            if(entity.location){
                SDL_Rect rect = {entity.location->xPixel,
                                 entity.location->yPixel,
                                 entity.location->width,
                                 entity.location->height};
                SDL_RenderCopy(this->renderer, entity.texture->texture, NULL, &rect);
            }
        }
    }
};
