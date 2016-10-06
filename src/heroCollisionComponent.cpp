#include "collisionComponent.h"

#include <iostream>

HeroCollisionComponent::HeroCollisionComponent(Entity* ent, Command* onEntity) :
    CollisionComponent(ent),
    entityCollisionCommand(onEntity) {
}

HeroCollisionComponent::~HeroCollisionComponent() {
    if (this->entityCollisionCommand)
        delete this->entityCollisionCommand;
}

Command* HeroCollisionComponent::onEntityCollision(Entity* /*other*/) {
    this->entity->score->addScore(100);
    this->entity->health->takeDamage(10);
    return this->entityCollisionCommand;
}

Command* HeroCollisionComponent::onBorderCollision() {
    return NULL;
}
