#include "collisionHandler.h"
#include <iostream>

CollisionHandler::CollisionHandler(std::vector<CollisionComponent*>& volList,
                                   std::vector<CollisionComponent*>& statList,
                                   const int w, const int h) :
    volatileList(volList),
    staticList(statList),
    width(w),
    height(h) {
}

void CollisionHandler::removeInvalidComponents() {
    std::vector<CollisionComponent*>::iterator it;
    for (it = this->staticList.begin(); it != this->staticList.end(); ) {
        if (!(*it)->isValid()) {
            *it = this->staticList.back();
            this->staticList.pop_back();
        } else
            ++it;
    }
    for (it = this->volatileList.begin(); it != this->volatileList.end(); ) {
        if (!(*it)->isValid()) {
            *it = this->volatileList.back();
            this->volatileList.pop_back();
        } else
            ++it;
    }
}

void CollisionHandler::handleCollisions(int dt) {
    this->removeInvalidComponents();

    // handle volatile components colliding with each other
    std::vector<CollisionComponent*>::const_iterator it;
    std::vector<CollisionComponent*>::const_iterator it2;
    for (it = this->volatileList.begin(); it != this->volatileList.end(); ++it) {
        CollisionComponent* comp1 = *it;
        //this->detectBorderCollision(comp1->entity);
        for (it2 = std::next(it, 1); it2 != this->volatileList.end(); ++it2) {
            CollisionComponent* comp2 = *it2;
            if (detectOverlap(comp1->entity, comp2->entity)) {
                comp1->onEntityCollision(comp2->entity, dt);
                comp2->onEntityCollision(comp1->entity, dt);
            }
        }
    }

    // handle volatile components colliding with static components
    for (it = this->volatileList.begin(); it != this->volatileList.end(); ++it) {
        CollisionComponent* comp1 = *it;
        //this->detectBorderCollision(comp1->entity);
        for (it2 = this->staticList.begin(); it2 != this->staticList.end(); ++it2) {
            CollisionComponent* comp2 = *it2;
            if (detectOverlap(comp1->entity, comp2->entity)) {
                comp1->onStaticCollision(comp2->entity);
                comp2->onEntityCollision(comp1->entity, dt);
            }
        }
    }
}

void CollisionHandler::borderBoundX(Entity* entity, float boundValue) {
    entity->x = boundValue;
    entity->physics->xVelocity = 0.0f;
    entity->collision->onBorderCollision();
}

void CollisionHandler::borderBoundY(Entity* entity, float boundValue) {
    entity->y = boundValue;
    entity->physics->yVelocity = 0.0f;
    entity->collision->onBorderCollision();
}

void CollisionHandler::detectBorderCollision(Entity *entity) {
    if (entity->collision) {
        if (entity->x < 0)
            this->borderBoundX(entity, 0.0f);
        else if (entity->x + entity->width > this->width)
            this->borderBoundX(entity, this->width - entity->width);

        if (entity->y < 0)
            this->borderBoundY(entity, 0.0f);
        else if (entity->y + entity->height > this->height)
            this->borderBoundY(entity, this->height - entity->height);
    }
}

// returns true if two entities overlap, false otherwise
bool CollisionHandler::detectOverlap(Entity* entity1, Entity* entity2) {
    //Calculate the sides of entity 1
    int leftA = entity1->x;
    int rightA = entity1->x + entity1->width;
    int topA = entity1->y;
    int bottomA = entity1->y + entity1->height;

    //Calculate the sides of entity 2
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
