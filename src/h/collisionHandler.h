#ifndef CORNERGAME_COLLISION_HANDLER_H
#define CORNERGAME_COLLISION_HANDLER_H

#include <list>
#include <map>
#include "collisionComponent.h"

class CollisionHandler {
private:
    std::map<int, CollisionComponent*>& componentMap;
    const int width;
    const int height;
    bool detectOverlap(Entity* entity1, Entity* entity2);
    void detectBorderCollision(Entity* entity);
public:
    CollisionHandler(std::map<int, CollisionComponent*>& componentMap,
                     const int w, const int h);
    void handleCollisions();
};

#endif
