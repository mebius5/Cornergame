#include "collisionComponent.h"

BombCollisionComponent::BombCollisionComponent(Entity* entity) :
    DynamicCollisionComponent(entity),
    exploded(false) {
}

void BombCollisionComponent::explode() {
    if (this->exploded)
        return;
    this->exploded = true;
    //TODO: activate other art
    // change width and height of collision space
}

void BombCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp) {
    if (otherComp->entity->health) {
        this->entity->physics->freeze();
        this->entity->physics->target = NULL;
        this->explode();
        otherComp->entity->health->takeDamage(50);
        otherComp->entity->actionState = ACTION_DAMAGE;
    }
}

void BombCollisionComponent::onStaticCollision(StaticCollisionComponent* otherComp) {
    if (dynamic_cast<TerrainCollisionComponent*>(otherComp)) {
        this->entity->physics->freeze();
        this->entity->physics->target = NULL;
        this->explode();
    }
}
