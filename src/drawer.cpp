#include <list>
#include "entity.h"
#include "system.h"


Drawer::Drawer(SDL_Renderer *renderer) {
    this->renderer = renderer;
}

void Drawer::draw(std::list <Entity> *entityList) {
    std::list<Entity>::const_iterator iterator;
    for(iterator = entityList->begin(); iterator != entityList->end(); ++iterator){
        Entity entity = * iterator;
        if(entity.texture){
            SDL_RenderCopy(this->renderer, entity.texture->texture, NULL, NULL);
        }
    }
};
