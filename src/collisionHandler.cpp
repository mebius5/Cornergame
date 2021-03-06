#include "collisionHandler.h"

CollisionHandler::CollisionHandler(std::vector<DynamicCollisionComponent*>& dynList,
                                   std::vector<StaticCollisionComponent*>& statList) :
    dynamicList(dynList),
    staticList(statList) {
}

void CollisionHandler::removeInvalidComponents() {
    std::vector<StaticCollisionComponent*>::iterator it;
    for (it = this->staticList.begin(); it != this->staticList.end(); ) {
        if (!(*it)->isValid()) {
            *it = this->staticList.back();
            this->staticList.pop_back();
        } else
            ++it;
    }
    std::vector<DynamicCollisionComponent*>::iterator it2;
    for (it2 = this->dynamicList.begin(); it2 != this->dynamicList.end(); ) {
        if (!(*it2)->isValid()) {
            *it2 = this->dynamicList.back();
            this->dynamicList.pop_back();
        } else
            ++it2;
    }
}

void CollisionHandler::handleCollisions() {
    this->removeInvalidComponents();

    // handle dynamic components colliding with each other
    std::vector<DynamicCollisionComponent*>::const_iterator it;
    std::vector<DynamicCollisionComponent*>::const_iterator it2;
    for (it = this->dynamicList.begin(); it != this->dynamicList.end(); ++it) {
        DynamicCollisionComponent* comp1 = *it;
        //this->detectBorderCollision(comp1->entity);
        for (it2 = std::next(it, 1); it2 != this->dynamicList.end(); ++it2) {
            DynamicCollisionComponent* comp2 = *it2;
            if (detectOverlap(comp1->entity, comp2->entity)) {
                comp1->onEntityCollision(comp2);
                comp2->onEntityCollision(comp1);
            }
        }
    }

    // handle dynamic components colliding with static components
    std::vector<StaticCollisionComponent*>::const_iterator it3;
    for (it = this->dynamicList.begin(); it != this->dynamicList.end(); ++it) {
        DynamicCollisionComponent* comp1 = *it;
        //this->detectBorderCollision(comp1->entity);
        for (it3 = this->staticList.begin(); it3 != this->staticList.end(); ++it3) {
            StaticCollisionComponent* comp2 = *it3;
            if (detectOverlap(comp1->entity, comp2->entity)) {
                comp2->onEntityCollision(comp1);
                comp1->onStaticCollision(comp2);
            }
        }
    }
}

// returns true if two entities overlap, false otherwise
bool CollisionHandler::detectOverlap(Entity* entity1, Entity* entity2) {
    //Calculate the sides of entity 1
    int leftA = (int) entity1->x;
    int rightA = (int) (entity1->x + entity1->width - 1);
    int topA = (int) entity1->y;
    int bottomA = (int) (entity1->y + entity1->height - 1);

    //Calculate the sides of entity 2
    int leftB = (int) entity2->x;
    int rightB = (int) (entity2->x + entity2->width - 1);
    int topB = (int) entity2->y;
    int bottomB = (int) (entity2->y + entity2->height - 1);

    //If any of the sides from A are outside of B, no overlap
    if (bottomA <= topB)
        return false;
    if (topA >= bottomB)
        return false;
    if (rightA <= leftB)
        return false;
    return leftA < rightB;

}
