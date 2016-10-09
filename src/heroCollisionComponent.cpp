#include "collisionComponent.h"

HeroCollisionComponent::HeroCollisionComponent(Entity* ent, Command* onEntity) :
    CollisionComponent(ent),
    entityCollisionCommand(onEntity) {
}

HeroCollisionComponent::~HeroCollisionComponent() {
    if (this->entityCollisionCommand)
        delete this->entityCollisionCommand;
}

void HeroCollisionComponent::onEntityCollision(Entity* other) {
    if(!(other->collision&& dynamic_cast<VictoryZoneCollisionComponent*>(other->collision))){
        //Avoid taking damage for colliding with victory zone
        this->entity->score->addScore(-20);
    }
    this->entity->health->takeDamage(10);
    if (this->entityCollisionCommand)
        Component::commandList->push_back(this->entityCollisionCommand);
}

void HeroCollisionComponent::onBorderCollision() {
}
