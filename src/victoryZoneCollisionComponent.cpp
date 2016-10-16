#include "collisionComponent.h"

VictoryZoneCollisionComponent::VictoryZoneCollisionComponent(Entity* ent, Command* onEntity) :
    CollisionComponent(ent, true),
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

void VictoryZoneCollisionComponent::onStaticCollision(Entity* /*other*/) {
}

void VictoryZoneCollisionComponent::onBorderCollision() {
}
