#include "collisionComponent.h"

EnemyCollisionComponent::EnemyCollisionComponent(Entity* entity) :
    DynamicCollisionComponent(entity) {
}

void EnemyCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp, int /*dt*/) {
    if (dynamic_cast<ProjectileCollisionComponent*>(otherComp)) {
        this->entity->health->takeDamage(200);
        this->entity->actionState = DAMAGE;
    }
}

void EnemyCollisionComponent::onStaticCollision(StaticCollisionComponent* /*otherComp*/) {
    this->entity->ai->resetAi();
    if (this->onGround || this->onLeftWall || this->onRightWall)
        (this->entity->physics)->resetJumps();
}

void EnemyCollisionComponent::onBorderCollision() {
    this->entity->ai->resetAi();
}
