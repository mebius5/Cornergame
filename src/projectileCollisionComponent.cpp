#include "collisionComponent.h"

ProjectileCollisionComponent::ProjectileCollisionComponent(Entity* entity, Command* entityCollisionCommand, int ownerID) :
    CollisionComponent(entity, false),
    entityCollisionCommand(entityCollisionCommand),
    ownerID(ownerID) {
}

void ProjectileCollisionComponent::onEntityCollision(Entity *other, int) {
	if(other->collision && other->getId() != this->ownerID) {
	    Component::commandList->push_back(this->entityCollisionCommand);
	}
}

void ProjectileCollisionComponent::onStaticCollision(Entity *) {
	Component::commandList->push_back(this->entityCollisionCommand);
}

void ProjectileCollisionComponent::onBorderCollision() {
}
