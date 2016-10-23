#ifndef CORNERGAME_COLLISION_HANDLER_H
#define CORNERGAME_COLLISION_HANDLER_H

#include <vector>
#include "collisionComponent.h"

class CollisionHandler {
private:
    std::vector<DynamicCollisionComponent*>& dynamicList;
    std::vector<StaticCollisionComponent*>& staticList;
    void removeInvalidComponents();
    bool detectOverlap(Entity* entity1, Entity* entity2);
public:
    CollisionHandler(std::vector<DynamicCollisionComponent*>& dynamicList,
                     std::vector<StaticCollisionComponent*>& staticList);
    void handleCollisions(int dt);
};

#endif
