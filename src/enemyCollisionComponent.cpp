#include "collisionComponent.h"

EnemyCollisionComponent::EnemyCollisionComponent(Entity* ent, Command* cmd) :
    CollisionComponent(ent),
    borderCollisionCommand(cmd) {
}

EnemyCollisionComponent::~EnemyCollisionComponent() {
    if (this->borderCollisionCommand)
        delete this->borderCollisionCommand;
}

Command* EnemyCollisionComponent::onEntityCollision(Entity* /*other*/) {
    this->entity->health->takeDamage(50);
    return NULL;
}

Command* EnemyCollisionComponent::onBorderCollision() {
    this->entity->ai->passCommand(this->borderCollisionCommand);
    return NULL;
}
