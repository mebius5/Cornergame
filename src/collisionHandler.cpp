#include "collisionHandler.h"

CollisionHandler::CollisionHandler(std::map<int, Entity*>& entityMap,
                                   std::list<Command*>& commandList,
                                   const int w, const int h) :
        entityMap(entityMap),
        commandList(commandList),
        width(w),
        height(h) {
}

void CollisionHandler::handleCollisions(){
    std::map<int, Entity*>::const_iterator it;
    std::map<int, Entity*>::const_iterator it2;
    for (it = this->entityMap.begin(); it != this->entityMap.end(); ++it) {
        Entity* e1 = it->second;
        if (e1->collision) {
            Command* collisionCmd1 = e1->collision->onEntityCollision;
            for (it2 = std::next(it, 1); it2 != entityMap.end(); ++it2) {
                Entity* e2 = it2->second;
                if (e1 != e2 && e2->collision && detectOverlap(e1, e2)) {
                    Command* collisionCmd2 = e2->collision->onEntityCollision;
                    if (collisionCmd1)
                        this->commandList.push_back(collisionCmd1);
                    if (collisionCmd2)
                        this->commandList.push_back(collisionCmd2);
                }
            }
        }

        this->handleBorderCollision(e1);
    }
}

void CollisionHandler::handleBorderCollision(Entity *entity){
    if (entity->collision) {
        Command* collisionCmd = entity->collision->onBorderCollision;
        if (entity->x < 0) {
            entity->x = 0;
            if (collisionCmd)
                this->commandList.push_back(collisionCmd);
        }

        if (entity->x + entity->width > this->width) {
            entity->x = this->width - entity->width;
            if (collisionCmd)
                this->commandList.push_back(collisionCmd);
        }

        if (entity->y < 0) {
            entity->y = 0;
            if (collisionCmd)
                this->commandList.push_back(collisionCmd);
        }

        if (entity->y + entity->height > this->height) {
            entity->y = this->height - entity->width;
            if (collisionCmd)
                this->commandList.push_back(collisionCmd);
        }
    }
}

// returns true if two entities overlap, false otherwise
bool CollisionHandler::detectOverlap(Entity* entity1, Entity* entity2) {
    //Calculate the sides of entity 1
    int leftA = entity1->x;
    int rightA = entity1->x + entity1->width;
    int topA = entity1->y;
    int bottomA = entity1->y + entity1->height;

    //Calculate the sides of entity 1
    int leftB = entity2->x;
    int rightB = entity2->x + entity2->width;
    int topB = entity2->y;
    int bottomB = entity2->y + entity2->height;

    //If any of the sides from A are outside of B, no overlap
    if (bottomA <= topB)
        return false;
    if (topA >= bottomB)
        return false;
    if (rightA <= leftB)
        return false;
    if (leftA >= rightB)
        return false;

    return true;
}
