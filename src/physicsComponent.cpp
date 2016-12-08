#include "physicsComponent.h"

PhysicsComponent::PhysicsComponent(Entity* entity) :
    Component(entity),
    jumpCommand(new PlaySoundCommand(SFX_JUMP)),
    startSlideCommand(new PlaySoundCommand(SFX_SCRAPE)),
    stopSlideCommand(new StopSoundCommand(SFX_SCRAPE)),
    timeSlowCommand(new TimeSlowCommand()),
    timeNormalCommand(new TimeNormalCommand()),
    xAccel(0.0f),
    yAccel(0.0f),
    accelAmount(.001f),
    slideVelocity(.1f),
    jumps(0),
    infiniteJumps(false),
    frozen(false),
    slow(false),
    aerialDodges(0),
    maxDodges(1),
    collisionComp(dynamic_cast<DynamicCollisionComponent*>(entity->collision)),
    xVelocity(0.0f),
    yVelocity(0.0f),
    maxXVelocity(.55f),
    maxYVelocity(2.0f),
    jumpVelocity(.5f),
    deceleration(.0018f),
    gravity(0.0022f),
    maxJumps(1),
    dodgeTime(-1),
    maxDodgeTime(600),
    target(NULL),
    rotSpeed(0.002f) {
}

PhysicsComponent::~PhysicsComponent() {
    if (this->jumpCommand)
        delete this->jumpCommand;
    if (this->startSlideCommand)
        delete this->startSlideCommand;
    if (this->stopSlideCommand)
        delete this->stopSlideCommand;
    if (this->timeSlowCommand)
        delete this->timeSlowCommand;
    if (this->timeNormalCommand)
        delete this->timeNormalCommand;
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

    // if we're frozen don't move
    if (this->frozen) {
        if (this->slow) {
            Component::commandList->push_back(this->timeNormalCommand);
            this->slow = false;
        }
        return;
    }

    if (onRightWall || onLeftWall) {
        if (this->startSlideCommand)
            Component::commandList->push_back(this->startSlideCommand);
    }

    // rotate velocities if homing on target
    if (target != NULL && !target->health->isValid()) {
        target = NULL;
    }
    if (target != NULL) {
        // figure out the direction to the target
        float xDir = this->target->x - this->entity->x;
        float yDir = this->target->y - this->entity->y;

        // compute the cross product with the velocity
        // if negative, the target is clockwise of velocity
        // if positive, the target is counterclockwise of velocity
        float crossprod = this->xVelocity * yDir - this->yVelocity * xDir;

        // perform the rotation
        float theta = this->rotSpeed * dt;
        if (crossprod < 0) {
            theta *= -1;
        }
        float newX = this->xVelocity * cos(theta) - this->yVelocity * sin(theta);
        float newY = this->xVelocity * sin(theta) + this->yVelocity * cos(theta);
        this->xVelocity = newX;
        this->yVelocity = newY;
    }

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

    if (this->dodgeTime >= 0) {
        this->xVelocity =
            this->maxXVelocity*this->entity->dir * this->dodgeTime/this->maxDodgeTime;
        this->yVelocity = 0;
        onGround = false;
    }

    // move entity based on velocity
    this->entity->x += this->xVelocity * dt;
    this->entity->y += this->yVelocity * dt;

    // apply death if out of bounds
    if (this->entity->health && this->entity->y > 1600) {
        this->entity->health->die();
    }

    if (!onRightWall && !onLeftWall) {
        if (this->stopSlideCommand)
            Component::commandList->push_back(this->stopSlideCommand);
    }

    // apply slow motion if close to target
    if (this->target && dynamic_cast<HeroInputComponent*>(this->target->input)
            && !this->target->health->isIsInvincible()
            && this->target->health->getHealth() <= 250) {
        if (abs((int)(this->entity->x - this->target->x)) < 100 &&
                abs((int)(this->entity->y - this->target->y)) < 100) {
            Component::commandList->push_back(this->timeSlowCommand);
            this->slow = true;
        } else if (this->slow) {
            Component::commandList->push_back(this->timeNormalCommand);
            this->slow = false;
        }
    }

    if (this->dodgeTime >= 0)
        this->dodgeTime -= dt;
}

void PhysicsComponent::freeze() {
    // let it go
    this->frozen = true;
}

bool PhysicsComponent::isFrozen() {
    return this->frozen;
}

void PhysicsComponent::jump(float velocity) {
    if (velocity == -1) {
        velocity = this->jumpVelocity;
    }
    if (this->jumps < this->maxJumps || this->infiniteJumps) {
        this->yVelocity = -1 * velocity;
        this->jumps++;
        this->entity->actionState = ACTION_JUMP;
        if (this->collisionComp->onLeftWall && !this->collisionComp->onGround)
            this->xVelocity = .25f * velocity;
        else if (this->collisionComp->onRightWall && !this->collisionComp->onGround)
            this->xVelocity = -.25f * velocity;
        if (this->jumpCommand)
            Component::commandList->push_back(this->jumpCommand);
        this->entity->particle->startSpawning(120, 180);
    }
}

void PhysicsComponent::resetJumps() {
    this->jumps = 0;
    this->aerialDodges = 0;
}

void PhysicsComponent::toggleInfiniteJumps() {
    this->infiniteJumps = !this->infiniteJumps;
    this->resetJumps();
}

void PhysicsComponent::bump(int dir) {
    this->xVelocity += dir * this->jumpVelocity;
    this->xVelocity = this->clipVelocity(this->xVelocity, this->maxXVelocity);
    this->dodgeTime = -1;
}

void PhysicsComponent::dodge(int dir) {
    if ((this->aerialDodges < this->maxDodges || this->infiniteJumps) && this->dodgeTime < 0) {
        this->dodgeTime = this->maxDodgeTime;
        this->xAccel = 0;
        this->yAccel = 0;
        this->entity->dir = dir;
        this->aerialDodges++;
        this->entity->actionState = ACTION_DODGE;
        static_cast<AnimationComponent*>(this->entity->art)->actionTime = 0;
    }
}

void PhysicsComponent::accelerateX(int dir) {
    if (this->dodgeTime < 0) {
        this->xAccel = dir * this->accelAmount;
        this->entity->dir = dir;
    }
}

void PhysicsComponent::accelerateY(int dir) {
    if (this->dodgeTime < 0)
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
