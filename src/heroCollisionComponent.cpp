#include "collisionComponent.h"

HeroCollisionComponent::HeroCollisionComponent(Command* onEntity) :
    CollisionComponent(NULL),
    entityCollisionCommand(onEntity) {
}

HeroCollisionComponent::~HeroCollisionComponent() {
    if (this->entityCollisionCommand)
        delete this->entityCollisionCommand;
}

Command* HeroCollisionComponent::onEntityCollision(Entity* /*other*/) {
    return this->entityCollisionCommand;
}

Command* HeroCollisionComponent::onBorderCollision() {
    return NULL;
}
