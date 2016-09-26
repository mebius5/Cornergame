#include "collisionHandler.h"

CollisionHandler::CollisionHandler(std::map<int, Entity*>& entityMap,
                                   std::list<Command*>& commandList,
                                   const int w, const int h) :
        entityMap(entityMap),
        commandList(commandList),
        width(w),
        height(h) {
}

void CollisionHandler::handleCollision(){
    std::map<int, Entity*>::const_iterator it;
    std::map<int, Entity*>::const_iterator it2;
    for (it = this->entityMap.begin(); it != this->entityMap.end(); ++it) {
        Entity* e1 = it->second;
        if (e1->location && e1->location->onEntityCollision) {
            for (it2 = std::next(it, 1); it2 != entityMap.end(); ++it2) {
                Entity* e2 = it2->second;
                if (e1 != e2 && e2->location && isRectOverlapping(e1, e2)) {
                    this->commandList.push_back(e1->location->onEntityCollision);
                    if (e2->location->onEntityCollision)
                        this->commandList.push_back(e2->location->onEntityCollision);
                }
            }
        }

        handleBorderCollision(e1);
    }
}

void CollisionHandler::handleBorderCollision(Entity *entity){
    if (entity->location && (entity->input || entity->ai)) {
        LocationComponent* loc = entity->location;
        if (loc->x < 0){
            loc->x = 0;
            if (loc->onBorderCollision)
                this->commandList.push_back(loc->onBorderCollision);
        }

        if (loc->x + loc->width > this->width) {
            loc->x = this->width - loc->width;
            if (loc->onBorderCollision)
                this->commandList.push_back(loc->onBorderCollision);
        }

        if (loc->y < 0) {
            loc->y = 0;
            if (loc->onBorderCollision)
                this->commandList.push_back(loc->onBorderCollision);
        }

        if (loc->y + loc->height > this->height) {
            loc->y = this->height - loc->width;
            if (loc->onBorderCollision)
                this->commandList.push_back(loc->onBorderCollision);
        }
    }
}

bool CollisionHandler::isRectOverlapping(Entity* entity1, Entity* entity2) {
    LocationComponent* a = entity1->location;
    LocationComponent* b = entity2->location;

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
