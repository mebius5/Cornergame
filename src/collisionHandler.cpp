#include "collisionHandler.h"

CollisionHandler::CollisionHandler(std::map<int, Entity*>& entityMap,
                                   std::list<Command*>& commandList,
                                   const int w, const int h):
        entityMap(entityMap), commandList(commandList), width(w), height(h) {
}

void CollisionHandler::handleCollision(){
    std::map<int, Entity*>::const_iterator it;
    std::map<int, Entity*>::const_iterator it2;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        Entity* e1 = it->second;
        if (e1->location && e1->location->onCollision) {
            for (it2 = std::next(it, 1); it2 != entityMap.end(); ++it2) {
                Entity* e2 = it2->second;
                if (e1 != e2 && e2->location) {
                    if (isRectOverlapping(e1->location, e2->location)) {
                        commandList.push_back(e1->location->onCollision);
                        if (e2->location->onCollision)
                            commandList.push_back(e2->location->onCollision);
                    }
                }
            }
        }

        handleBorderCollision(e1);
    }
}

void CollisionHandler::handleBorderCollision(Entity *entity){
    if (entity->input || entity->ai) {   //It's a moving character
        if(entity->location->x<0){
            entity->location->x=0;
        }

        if (entity->location->x+entity->location->width >this->width){
            entity->location->x = this->width - entity->location->width;
        }

        if (entity->location->y<0){
            entity->location->y=0;
        }

        if (entity->location->y+entity->location->height > this->height){
            entity->location->y = this->height - entity->location->width;
        }
    }
}

bool CollisionHandler::isRectOverlapping(LocationComponent* a,
                                         LocationComponent* b) {

    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a->x;
    rightA = a->x + a->width;
    topA = a->y;
    bottomA = a->y + a->height;

    //Calculate the sides of rect b
    leftB = b->x;
    rightB = b->x + b->width;
    topB = b->y;
    bottomB = b->y + b->height;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
