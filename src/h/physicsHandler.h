#ifndef CORNERGAME_PHYSICSHANDLER_H
#define CORNERGAME_PHYSICSHANDLER_H

#include "physicsComponent.h"

class PhysicsHandler {
    private:
        std::vector<PhysicsComponent*>& componentList;
    public:
        PhysicsHandler(std::vector<PhysicsComponent*>& componentList);
        void update(int dt);
};

#endif
