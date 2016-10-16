#ifndef CORNERGAME_COLLISION_HANDLER_H
#define CORNERGAME_COLLISION_HANDLER_H

#include <vector>
#include "collisionComponent.h"

class CollisionHandler {
private:
    std::vector<CollisionComponent*>& volatileList;
    std::vector<CollisionComponent*>& staticList;
    const int width;
    const int height;
    void removeInvalidComponents();
    void borderBoundX(Entity* entity, float boundValue);
    void borderBoundY(Entity* entity, float boundValue);
    bool detectOverlap(Entity* entity1, Entity* entity2);
    void detectBorderCollision(Entity* entity);
public:
    CollisionHandler(std::vector<CollisionComponent*>& volatileList,
                     std::vector<CollisionComponent*>& staticList,
                     const int w, const int h);
    void handleCollisions();
};

#endif
