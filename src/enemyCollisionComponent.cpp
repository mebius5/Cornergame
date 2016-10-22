#include "collisionComponent.h"

EnemyCollisionComponent::EnemyCollisionComponent(Entity* entity) :
    CollisionComponent(entity, false) {
}

void EnemyCollisionComponent::onEntityCollision(Entity *other, int /*dt*/) {
	if(other->collision && dynamic_cast<ProjectileCollisionComponent*>(other->collision)) {
	    this->entity->health->takeDamage(50);
	}
}

void EnemyCollisionComponent::onStaticCollision(Entity* /*other*/) {
    this->entity->ai->resetAi();
    if (this->entity->physics->yVelocity > 0)
        ((PhysicsComponent*)this->entity->physics)->resetJumps();
}

void EnemyCollisionComponent::onBorderCollision() {
    this->entity->ai->resetAi();
}
