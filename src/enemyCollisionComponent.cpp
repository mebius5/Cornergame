#include "collisionComponent.h"

EnemyCollisionComponent::EnemyCollisionComponent(Entity* entity) :
    CollisionComponent(entity, false) {
}

void EnemyCollisionComponent::onEntityCollision(Entity* /*other*/) {
    this->entity->health->takeDamage(30);
}

void EnemyCollisionComponent::onBorderCollision() {
    this->entity->ai->resetAi();
}
