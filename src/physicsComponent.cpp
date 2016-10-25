#include "physicsComponent.h"

PhysicsComponent::PhysicsComponent(Entity* entity) :
    Component(entity),
    xAccel(0.0f),
    yAccel(0.0f),
    accelAmount(.001f),
    gravity(0.0017f),
    jumps(0),
    infiniteJumps(false),
    collisionComp(dynamic_cast<DynamicCollisionComponent*>(entity->collision)),
    xVelocity(0.0f),
    yVelocity(0.0f),
    maxVelocity(.6f),
    jumpVelocity(.6f),
    deceleration(.0007f),
    maxJumps(1) {
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
    bool& onGround = this->collisionComp->onGround;
    bool& onLeftWall = this->collisionComp->onLeftWall;
    bool& onRightWall = this->collisionComp->onRightWall;

    // update velocities & flags based on acceleration
    this->xVelocity += this->xAccel * dt;
    if (this->xVelocity > 0 && onLeftWall)
        onLeftWall = false;
    if (this->xVelocity < 0 && onRightWall)
        onRightWall = false;
    this->xVelocity = this->clipVelocity(this->xVelocity);

    float finalYAccel = this->yAccel;
    if (!onGround)
        finalYAccel += this->gravity;

    this->yVelocity += finalYAccel * dt;
    if (this->yVelocity < 0 && onGround)
        onGround = false;
    this->yVelocity = this->clipVelocity(this->yVelocity);

    // account for sliding on walls
    float finalYVelocity = this->yVelocity;
    if ((onLeftWall || onRightWall) && this->yVelocity > 0) {
        finalYVelocity *= .125f;
    }

    // update flags if entity slides off platform/wall
    if (onGround && (this->entity->x > this->collisionComp->rightBound
            || this->entity->x + this->entity->width <= this->collisionComp->leftBound)) {
        onGround = false;
    }
    if ((onLeftWall || onRightWall) && (this->entity->y > this->collisionComp->topBound
            || this->entity->y + this->entity->height <= this->collisionComp->bottomBound)) {
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
    this->entity->y += finalYVelocity * dt;

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
    this->xVelocity = this->clipVelocity(this->xVelocity);
}

void PhysicsComponent::accelerateX(int dir) {
    this->xAccel = dir * this->accelAmount;
}

void PhysicsComponent::accelerateY(int dir) {
    this->yAccel = dir * this->accelAmount;
}

void PhysicsComponent::clearAccelerationX() {
    this->xAccel = 0;
}

void PhysicsComponent::clearAccelerationY() {
    this->yAccel = 0;
}
