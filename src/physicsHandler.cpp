#include "physicsHandler.h"

PhysicsHandler::PhysicsHandler(std::vector <PhysicsComponent*> &componentList):
    componentList(componentList) {
}

void PhysicsHandler::removeInvalidComponents() {
    std::vector<PhysicsComponent*>::iterator it;
    for (it = this->componentList.begin(); it != this->componentList.end(); ) {
        if (!(*it)->isValid()) {
            *it = this->componentList.back();
            this->componentList.pop_back();
        } else
            ++it;
    }
}

void PhysicsHandler::update(int dt) {
    this->removeInvalidComponents();

    std::vector<PhysicsComponent*>::iterator it;
    for (it = this->componentList.begin(); it != this->componentList.end(); ++it) {
        // handle physics
        PhysicsComponent * physComp = *it;
        physComp->updateLocation(dt);
    }
}
