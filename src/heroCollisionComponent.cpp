#include "collisionComponent.h"

HeroCollisionComponent::HeroCollisionComponent(Entity* ent, Command* onEntity) :
    CollisionComponent(ent, false),
    entityCollisionCommand(onEntity) {
}

HeroCollisionComponent::~HeroCollisionComponent() {
    if (this->entityCollisionCommand)
        delete this->entityCollisionCommand;
}

void HeroCollisionComponent::onEntityCollision(Entity* other) {
    if(other->collision && dynamic_cast<EnemyCollisionComponent*>(other->collision)){
        this->entity->score->addScore(-20);
        this->entity->health->takeDamage(10);
        if (this->entityCollisionCommand)
            Component::commandList->push_back(this->entityCollisionCommand);
    } else if (other->collision && dynamic_cast<ProjectileCollisionComponent*>(other->collision)) {
        ProjectileCollisionComponent* projectile = dynamic_cast<ProjectileCollisionComponent*>(other->collision);
        if (projectile->ownerID != this->entity->getId()) {
            this->entity->health->takeDamage(10);
        }
    } 
}

void HeroCollisionComponent::onStaticCollision(Entity* /*other*/) {
    if (this->entity->yVelocity > 0)
        ((HeroInputComponent*)this->entity->input)->resetJumps();
}

void HeroCollisionComponent::onBorderCollision() {
}
