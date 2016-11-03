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

        // knock back the other entity
        otherComp->entity->physics->bump(this->sign(this->entity->physics->xVelocity));
    }
}

void ProjectileCollisionComponent::onStaticCollision(StaticCollisionComponent* otherComp) {
    if (dynamic_cast<TerrainCollisionComponent*>(otherComp)) {
        Component::commandList->push_back(this->entityCollisionCommand);
    }
}

void ProjectileCollisionComponent::onBorderCollision() {
}
