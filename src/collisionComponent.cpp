#include "collisionComponent.h"

CollisionComponent::CollisionComponent(Command* onEntity, Command* onBorder) :
    Component(NULL),
    onEntityCollision(onEntity),
    onBorderCollision(onBorder) {
}

CollisionComponent::~CollisionComponent() {
    if (this->onEntityCollision)
        delete this->onEntityCollision;
    if (this->onBorderCollision)
        delete this->onBorderCollision;
}
