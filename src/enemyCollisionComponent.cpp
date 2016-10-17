#include "collisionComponent.h"

EnemyCollisionComponent::EnemyCollisionComponent(Entity* entity) :
    CollisionComponent(entity, false) {
}

void EnemyCollisionComponent::onEntityCollision(Entity* other) {
	if(other->collision && dynamic_cast<ProjectileCollisionComponent*>(other->collision)) {
	    this->entity->health->takeDamage(50);
	}
}

void EnemyCollisionComponent::onStaticCollision(Entity* /*other*/) {
    this->entity->ai->resetAi();
}

void EnemyCollisionComponent::onBorderCollision() {
    this->entity->ai->resetAi();
}
