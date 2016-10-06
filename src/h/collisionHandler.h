#ifndef CORNERGAME_COLLISION_HANDLER_H
#define CORNERGAME_COLLISION_HANDLER_H

#include "collisionComponent.h"
#include <list>
#include <map>

class CollisionHandler {
private:
    std::map<int, CollisionComponent*>& componentMap;
    std::list<Command*>& commandList;
    const int width;
    const int height;
    bool detectOverlap(Entity* entity1, Entity* entity2);
    void detectBorderCollision(Entity* entity);
public:
    CollisionHandler(std::map<int, CollisionComponent*>& componentMap,
                     std::list<Command*>& commandList,
                     const int w, const int h);
    void handleCollisions();
};

#endif
