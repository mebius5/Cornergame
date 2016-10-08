#include "collisionComponent.h"

HeroCollisionComponent::HeroCollisionComponent(Entity* ent, Command* onEntity) :
    CollisionComponent(ent),
    entityCollisionCommand(onEntity) {
}

HeroCollisionComponent::~HeroCollisionComponent() {
    if (this->entityCollisionCommand)
        delete this->entityCollisionCommand;
}

void HeroCollisionComponent::onEntityCollision(Entity* /*other*/) {
    this->entity->score->addScore(100);
    this->entity->health->takeDamage(10);
    if (this->entityCollisionCommand)
        Component::commandList->push_back(this->entityCollisionCommand);
}

void HeroCollisionComponent::onBorderCollision() {
}
