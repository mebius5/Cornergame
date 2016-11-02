#include "physicsComponent.h"
#include <iostream>

PhysicsComponent::PhysicsComponent(Entity* entity) :
    Component(entity),
    xAccel(0.0f),
    yAccel(0.0f),
    accelAmount(.001f),
    gravity(0.0018f),
    slideVelocity(.1f),
    jumps(0),
    infiniteJumps(false),
    collisionComp(dynamic_cast<DynamicCollisionComponent*>(entity->collision)),
    xVelocity(0.0f),
    yVelocity(0.0f),
    maxXVelocity(.55f),
    maxYVelocity(4.0f),
    jumpVelocity(.5f),
    deceleration(.0018f),
    maxJumps(1) {
}

PhysicsComponent::~PhysicsComponent() {
    this->entity = NULL;
}

float PhysicsComponent::clipVelocity(float velocity, float max) {
    // clip the absolute value of the velocity
    if (velocity > max) {
        velocity = max;
    } else if (velocity < -1 * max) {
        velocity = -1 * max;
    }
    return velocity;
}

void PhysicsComponent::updateLocation(int dt) {
    bool& onGround = this->collisionComp->onGround;
    bool& onLeftWall = this->collisionComp->onLeftWall;
    bool& onRightWall = this->collisionComp->onRightWall;

    // update velocities & flags based on acceleration
    this->xVelocity += this->xAccel * dt;
    if (this->xVelocity > 0 && onLeftWall)
        onLeftWall = false;
    if (this->xVelocity < 0 && onRightWall)
        onRightWall = false;
    this->xVelocity = this->clipVelocity(this->xVelocity, this->maxXVelocity);

    float finalYAccel = this->yAccel;
    if (!onGround)
        finalYAccel += this->gravity;

    this->yVelocity += finalYAccel * dt;
    if (this->yVelocity < 0 && onGround)
        onGround = false;
    this->yVelocity = this->clipVelocity(this->yVelocity, this->maxYVelocity);

    // account for sliding on walls
    if ((onLeftWall || onRightWall) && this->yVelocity > 0) {
        this->yVelocity = this->clipVelocity(this->yVelocity, this->slideVelocity);
    }

    // update flags if entity slides off platform/wall
    if (onGround && (this->entity->x > this->collisionComp->rightBound
            || this->entity->x + this->entity->width <= this->collisionComp->leftBound)) {
        onGround = false;
    }
    if ((onLeftWall || onRightWall) && (this->entity->y > this->collisionComp->bottomBound
            || this->entity->y + this->entity->height < this->collisionComp->topBound)) {
        onLeftWall = false;
        onRightWall = false;
    }

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

    // update acceleration and velocity based on these final flags
    if (onGround) {
        this->yVelocity = 0;
    }
    if (onLeftWall || onRightWall) {
        this->xVelocity = 0;
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
    if (this->jumps < this->maxJumps || this->infiniteJumps) {
        this->yVelocity = -1 * this->jumpVelocity;
        this->jumps++;
        this->entity->actionState = JUMP;
        if (this->collisionComp->onLeftWall && !this->collisionComp->onGround)
            this->xVelocity = .5f * this->jumpVelocity;
        else if (this->collisionComp->onRightWall && !this->collisionComp->onGround)
            this->xVelocity = -.5f * this->jumpVelocity;
    }
}

void PhysicsComponent::resetJumps() {
    this->jumps = 0;
}

void PhysicsComponent::toggleInfiniteJumps() {
    this->infiniteJumps = !this->infiniteJumps;
    this->resetJumps();
}

void PhysicsComponent::bump(int dir) {
    this->xVelocity += dir * this->jumpVelocity;
    this->xVelocity = this->clipVelocity(this->xVelocity, this->maxXVelocity);
}

void PhysicsComponent::accelerateX(int dir) {
    this->xAccel = dir * this->accelAmount;
}

void PhysicsComponent::accelerateY(int dir) {
    this->yAccel = dir * this->accelAmount;
}

void PhysicsComponent::clearAccelerationX() {
    this->xAccel = 0;
    this->collisionComp->onLeftWall = false;
    this->collisionComp->onRightWall = false;
}

void PhysicsComponent::clearAccelerationY() {
    this->yAccel = 0;
}

bool PhysicsComponent::isInfiniteJumpOn() {
    return this->infiniteJumps;
}
