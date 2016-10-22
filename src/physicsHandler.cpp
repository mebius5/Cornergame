#include "physicsHandler.h"

PhysicsHandler::PhysicsHandler(std::vector <PhysicsComponent*> &componentList):
    componentList(componentList) {
}

void PhysicsHandler::update(int dt) {
    std::vector<PhysicsComponent*>::iterator it;
    for (it = this->componentList.begin(); it != this->componentList.end(); ) {
        if (!(*it)->isValid()) {        // remove invalid components
            *it = this->componentList.back();
            this->componentList.pop_back();
            continue;
        }
        // handle physics
        PhysicsComponent * physComp = *it;
        physComp->updateLocation(dt);
        ++it;
    }
}
