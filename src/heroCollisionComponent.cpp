#include "collisionComponent.h"

#include <iostream>

HeroCollisionComponent::HeroCollisionComponent(Command* onEntity, Entity* entity) :
    CollisionComponent(entity),
    entityCollisionCommand(onEntity) {
}

HeroCollisionComponent::~HeroCollisionComponent() {
    if (this->entityCollisionCommand)
        delete this->entityCollisionCommand;
}

Command* HeroCollisionComponent::onEntityCollision(Entity* /*other*/) {
    this->entity->score->addScore(100);
    std::cout << this->entity->score->getScore() << std::endl;
    return this->entityCollisionCommand;
}

Command* HeroCollisionComponent::onBorderCollision() {
    return NULL;
}
