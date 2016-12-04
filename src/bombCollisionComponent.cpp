#include "collisionComponent.h"

BombCollisionComponent::BombCollisionComponent(Entity* entity, Command* cmd) :
    DynamicCollisionComponent(entity),
    despawnCommand(cmd) {
}

BombCollisionComponent::~BombCollisionComponent() {
    if (this->despawnCommand)
        delete this->despawnCommand;
}

void BombCollisionComponent::onEntityCollision(DynamicCollisionComponent* /*otherComp*/) {

}

void BombCollisionComponent::onStaticCollision(StaticCollisionComponent* /*otherComp*/) {

}
