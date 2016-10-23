#include "collisionComponent.h"

ProjectileCollisionComponent::ProjectileCollisionComponent(Entity* entity, Command* cmd, int ownerID) :
    DynamicCollisionComponent(entity),
    entityCollisionCommand(cmd),
    ownerID(ownerID) {
}

ProjectileCollisionComponent::~ProjectileCollisionComponent() {
    if (this->entityCollisionCommand)
        delete this->entityCollisionCommand;
}

void ProjectileCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp, int /*dt*/) {
    if (otherComp->entity->getId() != this->ownerID) {
        Component::commandList->push_back(this->entityCollisionCommand);
    }
}

void ProjectileCollisionComponent::onStaticCollision(StaticCollisionComponent* /*otherComp*/) {
    Component::commandList->push_back(this->entityCollisionCommand);
}

void ProjectileCollisionComponent::onBorderCollision() {
}
