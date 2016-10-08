#include "collisionComponent.h"

VictoryZoneCollisionComponent::VictoryZoneCollisionComponent(Entity* ent, Command* onEntity) :
    CollisionComponent(ent),
    entityCollisionCommand(onEntity) {
}

VictoryZoneCollisionComponent::~VictoryZoneCollisionComponent() {
    if (this->entityCollisionCommand)
        delete this->entityCollisionCommand;
}

void VictoryZoneCollisionComponent::onEntityCollision(Entity* other) {
    if (other->input)   // if hero, enter victory state
        Component::commandList->push_back(this->entityCollisionCommand);
}

void VictoryZoneCollisionComponent::onBorderCollision() {
}
