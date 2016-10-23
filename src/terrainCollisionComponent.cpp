#include "collisionComponent.h"

TerrainCollisionComponent::TerrainCollisionComponent(Entity *entity,
                bool freeTop, bool freeBot, bool freeRight, bool freeLeft):
    StaticCollisionComponent(entity),
    freeTop(freeTop),
    freeBot(freeBot),
    freeRight(freeRight),
    freeLeft(freeLeft) {
}

void TerrainCollisionComponent::onEntityCollision(DynamicCollisionComponent* otherComp, int /*dt*/) {
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

    // resolve collisions
    float crossProduct;
    if (collideTopLeft) {
        crossProduct = -(rightO-leftT) * yVelocity + (bottomO-topT) * xVelocity;
        if (crossProduct > 0) {       // velocity vector to the left of collision vector
            this->boundX(otherComp, leftT - other->width, topT, bottomT);
            otherComp->onRightWall = true;       // bound with terrain left side
        } else {                      // velocity vector to the right of collision vector
            this->boundY(otherComp, topT - other->height, leftT, rightT);
            otherComp->onGround = true;         // bound with terrain top
        }
    } else if (collideTopRight) {
        crossProduct = -(leftO-rightT) * yVelocity + (bottomO-topT) * xVelocity;
        if (crossProduct > 0) {
            this->boundY(otherComp, topT - other->height, leftT, rightT);
            otherComp->onGround = true;
        } else {
            this->boundX(otherComp, rightT, topT, bottomT);
            otherComp->onLeftWall = true;
        }
    } else if (collideBottomLeft) {
        crossProduct = -(rightO-leftT) * yVelocity + (topO-bottomT) * xVelocity;
        if (crossProduct > 0)
            this->boundY(otherComp, bottomT, leftT, rightT);
        else {
            this->boundX(otherComp, leftT - other->width, topT, bottomT);
            otherComp->onRightWall = true;
        }
    } else if (collideBottomRight) {
        crossProduct = -(leftO-rightT) * yVelocity + (topO-bottomT) * xVelocity;
        if (crossProduct > 0) {
            this->boundX(otherComp, rightT, topT, bottomT);
            otherComp->onLeftWall = true;
        } else
            this->boundY(otherComp, bottomT, leftT, rightT);
    } else if (collideBottom) {     // object collide's with bottom of terrain
        this->boundY(otherComp, bottomT, leftT, rightT);
    } else if (collideTop) {        // object collide from above
        this->boundY(otherComp, topT - other->height, leftT, rightT);
        otherComp->onGround = true;
    } else if (collideRight) {      // object collide from right
        this->boundX(otherComp, rightT, topT, bottomT);
        otherComp->onLeftWall = true;
    } else if (collideLeft) {       // object collide from left
        this->boundX(otherComp, leftT - other->width, topT, bottomT);
        otherComp->onRightWall = true;
    }
}

void TerrainCollisionComponent::onBorderCollision() {
}

void TerrainCollisionComponent::boundX(DynamicCollisionComponent* otherComp, float boundValue,
                                       int topT, int bottomT) {
    Entity* other = otherComp->entity;
    other->x = boundValue;
    other->physics->xVelocity = 0.0f;
    otherComp->topBound = topT;
    otherComp->bottomBound = bottomT;
}

void TerrainCollisionComponent::boundY(DynamicCollisionComponent* otherComp, float boundValue,
                                       int leftT, int rightT) {
    Entity* other = otherComp->entity;
    other->y = boundValue;
    other->physics->yVelocity = 0.0f;
    otherComp->leftBound = leftT;
    otherComp->rightBound = rightT;
}
