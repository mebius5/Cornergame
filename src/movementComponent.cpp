#include "movementComponent.h"

MovementComponent::MovementComponent(Entity* entity) :
    PhysicsComponent(entity) {
}

void MovementComponent::updateLocation(int dt) {
    // move entity based on velocity
    this->entity->x += this->xVelocity * dt;
    this->entity->y += this->yVelocity * dt;
}
