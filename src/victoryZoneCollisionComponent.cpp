#include "collisionComponent.h"

VictoryZoneCollisionComponent::VictoryZoneCollisionComponent(Entity* ent, Command* onEntity) :
    StaticCollisionComponent(ent),
    entityCollisionCommand(onEntity) {
}

VictoryZoneCollisionComponent::~VictoryZoneCollisionComponent() {
    if (this->entityCollisionCommand)
        delete this->entityCollisionCommand;
}

void VictoryZoneCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp) {
    if (otherComp->entity->input)   // if hero, enter victory state
        Component::commandList->push_back(this->entityCollisionCommand);
}
