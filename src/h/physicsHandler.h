#ifndef CORNERGAME_PHYSICS_HANDLER_H
#define CORNERGAME_PHYSICS_HANDLER_H

#include "physicsComponent.h"

class PhysicsHandler {
private:
    std::vector<PhysicsComponent*>& componentList;
public:
    PhysicsHandler(std::vector<PhysicsComponent*>& componentList);
    void update(int dt);
};

#endif
