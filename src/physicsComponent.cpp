#include "physicsComponent.h"

PhysicsComponent::PhysicsComponent(Entity* entity) :
    Component(entity),
    xAccel(0.0f),
    yAccel(0.0f),
    accelAmount(.001f),
    gravity(0.0017f),
    jumps(0),
    infiniteJumps(false),
    xVelocity(0.0f),
    yVelocity(0.0f),
    maxVelocity(.6f),
    deceleration(.001f),
    maxJumps(2) {
    this->yAccel = this->gravity;
}

PhysicsComponent::~PhysicsComponent() {
    this->entity = NULL;
}

float PhysicsComponent::clipVelocity(float velocity) {
    // clip the absolute value of the velocity
    if (velocity > this->maxVelocity) {
        velocity = this->maxVelocity;
    } else if (velocity < -1 * this->maxVelocity) {
        velocity = -1 * this->maxVelocity;
    }
    return velocity;
}

void PhysicsComponent::updateLocation(int dt) {
    // update velocities based on acceleration
    this->xVelocity += this->xAccel * dt;
    this->xVelocity = this->clipVelocity(this->xVelocity);
    this->yVelocity += this->yAccel * dt;
    this->yVelocity = this->clipVelocity(this->yVelocity);

    // apply friction if not accelerating
    if (this->xAccel == 0) {
        if (this->xVelocity > this->deceleration * dt) {
            this->xVelocity -= this->deceleration * dt;
        } else if (this->xVelocity < -1 * this->deceleration * dt) {
            this->xVelocity += this->deceleration * dt;
        } else {
            this->xVelocity = 0;
        }
    }

    // move entity based on velocity
    this->entity->x += this->xVelocity * dt;
    this->entity->y += this->yVelocity * dt;

    // apply death if out of bounds
    // TODO move this somewhere else
    if (this->entity->health && this->entity->y > 1600) {
        this->entity->health->die();
    }
}

void PhysicsComponent::jump() {
    if ((this->jumps < this->maxJumps && this->yVelocity >= 0.0f) || this->infiniteJumps) {
        this->yVelocity = -1 * this->maxVelocity;
        this->jumps += 1;
    }
}

void PhysicsComponent::resetJumps() {
    this->jumps = 0;
}

void PhysicsComponent::toggleInfiniteJumps() {
    this->infiniteJumps = !this->infiniteJumps;
    this->resetJumps();
}

void PhysicsComponent::accelerateX(int dir) {
    this->xAccel = dir * this->accelAmount;
}

void PhysicsComponent::accelerateY(int dir) {
    this->yAccel = dir * this->accelAmount + this->gravity;
}

void PhysicsComponent::clearAccelerationX() {
    this->xAccel = 0;
}

void PhysicsComponent::clearAccelerationY() {
    this->yAccel = this->gravity;
}

// void PhysicsComponent::startSliding() {
//     this->maxVelocity /= 2;
// }
//
// void PhysicsComponent::stopSliding() {
//     this->maxVelocity *= 2;
// }
