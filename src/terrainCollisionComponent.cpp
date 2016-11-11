#include "collisionComponent.h"

TerrainCollisionComponent::TerrainCollisionComponent(Entity *entity,
                bool freeTop, bool freeBot, bool freeRight, bool freeLeft):
    StaticCollisionComponent(entity),
    landCommand(new PlaySoundCommand(SFX_LAND)),
    freeTop(freeTop),
    freeBot(freeBot),
    freeRight(freeRight),
    freeLeft(freeLeft) {
}

TerrainCollisionComponent::~TerrainCollisionComponent() {
    if (this->landCommand)
        delete this->landCommand;
}

void TerrainCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp) {
    Entity* other = otherComp->entity;
    //Calculate the sides of entity 1
    int leftT = this->entity->x;
    int rightT = this->entity->x + this->entity->width;
    int topT = this->entity->y;
    int bottomT = this->entity->y + this->entity->height;

    //Calculate the sides of entity 2
    int leftO = other->x;
    int rightO = other->x + other->width;
    int topO = other->y;
    int bottomO = other->y + other->height;

    // is there a collision on terrain's bottom? top? right? left? corners?
    float xVelocity = other->physics->xVelocity;
    float yVelocity = other->physics->yVelocity;
    bool collideBottom = this->freeBot && bottomT > topO && yVelocity <= 0;
    bool collideTop = this->freeTop && topT < bottomO && yVelocity >= 0;
    bool collideRight = this->freeRight && rightT > leftO && xVelocity <= 0;
    bool collideLeft = this->freeLeft && leftT < rightO && xVelocity >= 0;
    bool collideTopLeft = collideTop && collideLeft && !collideBottom && !collideRight;
    bool collideTopRight = collideTop && collideRight && !collideBottom && !collideLeft;
    bool collideBottomLeft = collideBottom && collideLeft && !collideTop && !collideRight;
    bool collideBottomRight = collideBottom && collideRight && !collideTop && !collideLeft;

    // ignore projectiles
    if (dynamic_cast<ProjectileCollisionComponent*>(otherComp)) {
        return;
    }

    // resolve collisions
    float crossProduct;
    if (collideTopLeft) {
        crossProduct = -(rightO-leftT) * yVelocity + (bottomO-topT) * xVelocity;
        if (crossProduct > 0)     // velocity vector to the left of collision vector
            this->collideRightWall(otherComp, leftT - other->width, topT, bottomT); // bound with terrain left side
        else                      // velocity vector to the right of collision vector
            this->collideGround(otherComp, topT - other->height, leftT, rightT); // bound with terrain top
    } else if (collideTopRight) {
        crossProduct = -(leftO-rightT) * yVelocity + (bottomO-topT) * xVelocity;
        if (crossProduct > 0)
            this->collideGround(otherComp, topT - other->height, leftT, rightT);
        else
            this->collideLeftWall(otherComp, rightT, topT, bottomT);
    } else if (collideBottomLeft) {
        crossProduct = -(rightO-leftT) * yVelocity + (topO-bottomT) * xVelocity;
        if (crossProduct > 0)
            this->boundY(otherComp, bottomT);
        else
            this->collideRightWall(otherComp, leftT - other->width, topT, bottomT);
    } else if (collideBottomRight) {
        crossProduct = -(leftO-rightT) * yVelocity + (topO-bottomT) * xVelocity;
        if (crossProduct > 0)
            this->collideLeftWall(otherComp, rightT, topT, bottomT);
        else
            this->boundY(otherComp, bottomT);
    } else if (collideBottom && !collideTop)     // object collide's with bottom of terrain
        this->boundY(otherComp, bottomT);
    else if (collideTop && !collideBottom)       // object collide from above
        this->collideGround(otherComp, topT - other->height, leftT, rightT);
    else if (collideRight && !collideLeft)       // object collide from right
        this->collideLeftWall(otherComp, rightT, topT, bottomT);
    else if (collideLeft && !collideRight)       // object collide from left
        this->collideRightWall(otherComp, leftT - other->width, topT, bottomT);
}

void TerrainCollisionComponent::onBorderCollision() {
}

void TerrainCollisionComponent::collideLeftWall(DynamicCollisionComponent* otherComp,
                                                  float boundValue, int topT, int bottomT) {
    if (otherComp->onLeftWall) {
        otherComp->topBound = std::min(otherComp->topBound, topT);
        otherComp->bottomBound = std::max(otherComp->bottomBound, bottomT);
    } else {
        otherComp->onLeftWall = true;
        otherComp->topBound = topT;
        otherComp->bottomBound = bottomT;
    }
    this->boundX(otherComp, boundValue);
}

void TerrainCollisionComponent::collideRightWall(DynamicCollisionComponent* otherComp,
                                                   float boundValue, int topT, int bottomT) {
    if (otherComp->onRightWall) {
        otherComp->topBound = std::min(otherComp->topBound, topT);
        otherComp->bottomBound = std::max(otherComp->bottomBound, bottomT);
    } else {
        otherComp->onRightWall = true;
        otherComp->topBound = topT;
        otherComp->bottomBound = bottomT;
    }
    this->boundX(otherComp, boundValue);
}

void TerrainCollisionComponent::collideGround(DynamicCollisionComponent* otherComp,
                                             float boundValue, int leftT, int rightT) {
    if (otherComp->onGround) {
        otherComp->leftBound = std::min(otherComp->leftBound, leftT);
        otherComp->rightBound = std::max(otherComp->rightBound, rightT);
    } else {
        otherComp->onGround = true;
        otherComp->leftBound = leftT;
        otherComp->rightBound = rightT;
    }
    this->boundY(otherComp, boundValue);
}

void TerrainCollisionComponent::boundX(DynamicCollisionComponent* otherComp,
                                       float boundValue) {
    Entity* other = otherComp->entity;
    other->x = boundValue;
    other->physics->xVelocity = 0.0f;
}

void TerrainCollisionComponent::boundY(DynamicCollisionComponent* otherComp,
                                       float boundValue) {
    Entity* other = otherComp->entity;
    other->y = boundValue;
    other->physics->yVelocity = 0.0f;
}
