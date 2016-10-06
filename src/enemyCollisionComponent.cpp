#include "collisionComponent.h"

EnemyCollisionComponent::EnemyCollisionComponent(Entity* entity) :
    CollisionComponent(entity) {
}

Command* EnemyCollisionComponent::onEntityCollision(Entity* /*other*/) {
    this->entity->health->takeDamage(50);
    return NULL;
}

Command* EnemyCollisionComponent::onBorderCollision() {
    this->entity->ai->resetAi();
    return NULL;
}
