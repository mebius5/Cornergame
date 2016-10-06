#include "collisionHandler.h"

CollisionHandler::CollisionHandler(std::map<int, CollisionComponent*>& compMap,
                                   std::list<Command*>& commandList,
                                   const int w, const int h) :
    componentMap(compMap),
    commandList(commandList),
    width(w),
    height(h) {
}

void CollisionHandler::handleCollisions(){
    std::map<int, CollisionComponent*>::const_iterator it;
    std::map<int, CollisionComponent*>::const_iterator it2;
    Command* collisionCmd = NULL;
    for (it = this->componentMap.begin(); it != this->componentMap.end(); ++it){
        CollisionComponent* comp1 = it->second;
        for (it2 = std::next(it, 1); it2 != this->componentMap.end(); ++it2) {
            CollisionComponent* comp2 = it2->second;
            if (comp1 != comp2 && detectOverlap(comp1->entity, comp2->entity)) {
                collisionCmd = comp1->onEntityCollision(comp2->entity);
                if (collisionCmd)
                    this->commandList.push_back(collisionCmd);
                collisionCmd = comp2->onEntityCollision(comp1->entity);
                if (collisionCmd)
                    this->commandList.push_back(collisionCmd);
            }
        }

        this->detectBorderCollision(comp1->entity);
    }
}

void CollisionHandler::detectBorderCollision(Entity *entity) {
    Command* collisionCmd = NULL;
    if (entity->collision) {
        if (entity->x < 0) {
            entity->x = 0;
            entity->xVelocity = 0.0f;
            collisionCmd = entity->collision->onBorderCollision();
            if (collisionCmd)
                this->commandList.push_back(collisionCmd);
        }

        if (entity->x + entity->width > this->width) {
            entity->x = this->width - entity->width;
            entity->xVelocity = 0.0f;
            collisionCmd = entity->collision->onBorderCollision();
            if (collisionCmd)
                this->commandList.push_back(collisionCmd);
        }

        if (entity->y < 0) {
            entity->y = 0;
            entity->yVelocity = 0.0f;
            collisionCmd = entity->collision->onBorderCollision();
            if (collisionCmd)
                this->commandList.push_back(collisionCmd);
        }

        if (entity->y + entity->height > this->height) {
            entity->y = this->height - entity->width;
            entity->yVelocity = 0.0f;
            collisionCmd = entity->collision->onBorderCollision();
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
