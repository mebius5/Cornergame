#include "collisionComponent.h"

ProjectileCollisionComponent::ProjectileCollisionComponent(Entity* entity, Command* cmd, int ownerID) :
    CollisionComponent(entity, false),
    entityCollisionCommand(cmd),
    ownerID(ownerID) {
}

ProjectileCollisionComponent::~ProjectileCollisionComponent() {
    if (this->entityCollisionCommand)
        delete this->entityCollisionCommand;
}

void ProjectileCollisionComponent::onEntityCollision(Entity *other, int /*dt*/) {
    if(other->getId() != this->ownerID) {
        Component::commandList->push_back(this->entityCollisionCommand);
    }
}

void ProjectileCollisionComponent::onStaticCollision(Entity* /*other*/) {
    Component::commandList->push_back(this->entityCollisionCommand);
}

void ProjectileCollisionComponent::onBorderCollision() {
}
