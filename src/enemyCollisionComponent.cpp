#include "collisionComponent.h"

EnemyCollisionComponent::EnemyCollisionComponent(Entity* entity) :
    CollisionComponent(entity) {
}

void EnemyCollisionComponent::onEntityCollision(Entity* /*other*/) {
    this->entity->health->takeDamage(50);
}

void EnemyCollisionComponent::onBorderCollision() {
    this->entity->ai->resetAi();
}
