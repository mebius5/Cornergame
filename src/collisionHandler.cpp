#include "collisionHandler.h"

CollisionHandler::CollisionHandler(std::vector<CollisionComponent*>& compList,
                                   const int w, const int h) :
    componentList(compList),
    width(w),
    height(h) {
}

void CollisionHandler::removeInvalidComponents() {
    std::vector<CollisionComponent*>::iterator it;
    for (it = this->componentList.begin(); it != this->componentList.end(); ) {
        if (!(*it)->isValid()) {
            *it = this->componentList.back();
            this->componentList.pop_back();
        } else
            ++it;
    }
}

void CollisionHandler::handleCollisions() {
    this->removeInvalidComponents();

    std::vector<CollisionComponent*>::const_iterator it;
    std::vector<CollisionComponent*>::const_iterator it2;
    for (it = this->componentList.begin(); it != this->componentList.end(); ++it) {
        CollisionComponent* comp1 = *it;
        this->detectBorderCollision(comp1->entity);
        for (it2 = std::next(it, 1); it2 != this->componentList.end(); ++it2) {
            CollisionComponent* comp2 = *it2;
            if (detectOverlap(comp1->entity, comp2->entity)) {
                comp1->onEntityCollision(comp2->entity);
                comp2->onEntityCollision(comp1->entity);
            }
        }
    }
}

void CollisionHandler::borderBoundX(Entity* entity, float boundValue) {
    entity->x = boundValue;
    entity->xVelocity = 0.0f;
    entity->collision->onBorderCollision();
}

void CollisionHandler::borderBoundY(Entity* entity, float boundValue) {
    entity->y = boundValue;
    entity->yVelocity = 0.0f;
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
