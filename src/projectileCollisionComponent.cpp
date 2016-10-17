#include "collisionComponent.h"

ProjectileCollisionComponent::ProjectileCollisionComponent(Entity* entity, Command* entityCollisionCommand) :
    CollisionComponent(entity, false),
    entityCollisionCommand(entityCollisionCommand) {
}

void ProjectileCollisionComponent::onEntityCollision(Entity* other) {
	if(other->collision && !dynamic_cast<HeroCollisionComponent*>(other->collision)) {
	    //Component::commandList->push_back(this->entityCollisionCommand);
	}
}

void ProjectileCollisionComponent::onStaticCollision(Entity* /*other*/) {
	Component::commandList->push_back(this->entityCollisionCommand);
}

void ProjectileCollisionComponent::onBorderCollision() {
}
