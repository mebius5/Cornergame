#include "collisionComponent.h"

TerrainCollisionComponent::TerrainCollisionComponent(Entity *entity,
 bool freeTop, bool freeBot, bool freeRight, bool freeLeft):
    CollisionComponent(entity, true),
    freeTop(freeTop),
    freeBot(freeBot),
    freeRight(freeRight),
    freeLeft(freeLeft) {
}

void TerrainCollisionComponent::onEntityCollision(Entity *other) {
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
    bool collideBottom = this->freeBot && bottomT > topO && other->physics->yVelocity <= 0;
    bool collideTop = this->freeTop && topT < bottomO && other->physics->yVelocity >= 0;
    bool collideRight = this->freeRight && rightT > leftO && other->physics->xVelocity <= 0;
    bool collideLeft = this->freeLeft && leftT < rightO && other->physics->xVelocity >= 0;
    bool collideTopLeft = collideTop && collideLeft && !collideBottom && !collideRight;
    bool collideTopRight = collideTop && collideRight && !collideBottom && !collideLeft;
    bool collideBottomLeft = collideBottom && collideLeft && !collideTop && !collideRight;
    bool collideBottomRight = collideBottom && collideRight && !collideTop && !collideLeft;

    // resolve collisions
    float crossProduct;
    if (collideTopLeft) {
        crossProduct = -(rightO-leftT) * other->physics->yVelocity + (bottomO-topT) * other->physics->xVelocity;
        if (crossProduct > 0)       // velocity vector to the left of collision vector
            borderBoundX(other, leftT - other->width); // bound with terrain left side
        else                        // velocity vector to the right of collision vector
            borderBoundY(other, topT - other->height); // bound with terrain top
    } else if (collideTopRight) {
        crossProduct = -(leftO-rightT) * other->physics->yVelocity + (bottomO-topT) * other->physics->xVelocity;
        if (crossProduct > 0)
            borderBoundY(other, topT - other->height);
        else
            borderBoundX(other, rightT);
    } else if (collideBottomLeft) {
        crossProduct = -(rightO-leftT) * other->physics->yVelocity + (topO-bottomT) * other->physics->xVelocity;
        if (crossProduct > 0)
            borderBoundY(other, bottomT);
        else
            borderBoundX(other, leftT - other->width);
    } else if (collideBottomRight) {
        crossProduct = -(leftO-rightT) * other->physics->yVelocity + (topO-bottomT) * other->physics->xVelocity;
        if (crossProduct > 0)
            borderBoundX(other, rightT);
        else
            borderBoundY(other, bottomT);
    } else if (collideBottom) {
        borderBoundY(other, bottomT);
    } else if (collideTop) { //object collide from above
         borderBoundY(other, topT - other->height);
    } else if (collideRight) { //object collide from right
         borderBoundX(other, rightT);
    } else if (collideLeft) { // object collide from left
         borderBoundX(other, leftT - other->width);
    }
}

void TerrainCollisionComponent::onStaticCollision(Entity* /*other*/) {
}

void TerrainCollisionComponent::onBorderCollision() {
}

void TerrainCollisionComponent::borderBoundX(Entity* other, float boundValue) {
    other->x = boundValue;
    other->physics->xVelocity = 0.0f;
}

void TerrainCollisionComponent::borderBoundY(Entity* other, float boundValue) {
    other->y = boundValue;
    other->physics->yVelocity = 0.0f;
}
