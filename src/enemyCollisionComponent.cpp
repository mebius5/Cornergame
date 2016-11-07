#include "collisionComponent.h"

EnemyCollisionComponent::EnemyCollisionComponent(Entity* entity) :
    DynamicCollisionComponent(entity),
    projCollisionCommand(new PlaySoundCommand(SFX_ENEMY)) {
}

EnemyCollisionComponent::~EnemyCollisionComponent() {
    if (this->projCollisionCommand)
        delete this->projCollisionCommand;
}

void EnemyCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp) {
    if (dynamic_cast<ProjectileCollisionComponent*>(otherComp)) {
        if (this->projCollisionCommand)
            Component::commandList->push_back(this->projCollisionCommand);
    }
    otherComp->entity->physics->bump(this->sign(otherComp->entity->x + otherComp->entity->width/2 -
                                                this->entity->x - this->entity->width/2));
}

void EnemyCollisionComponent::onStaticCollision(StaticCollisionComponent* /*otherComp*/) {
    this->entity->ai->resetAi();
    if (this->onGround || this->onLeftWall || this->onRightWall)
        (this->entity->physics)->resetJumps();
}

void EnemyCollisionComponent::onBorderCollision() {
    this->entity->ai->resetAi();
}
