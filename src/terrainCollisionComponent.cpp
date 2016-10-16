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

    // is there a collision on terrain's bottom? top? right? left?
    bool collideBottom = this->freeBot && bottomT > topO && bottomO > bottomT;
    bool collideTop = this->freeTop && topT < bottomO && topO < topT;
    bool collideRight = this->freeRight && rightT > leftO && rightO > rightT;
    bool collideLeft = this->freeLeft && leftT < rightO && leftO < leftT;
    bool collideTopLeft = collideTop && collideLeft && !collideBottom && !collideRight;
    bool collideTopRight = collideTop && collideRight && !collideBottom && !collideLeft;
    bool collideBottomLeft = collideBottom && collideLeft && !collideTop && !collideRight;
    bool collideBottomRight = collideBottom && collideRight && !collideTop && !collideLeft;



    if (collideBottom)
         borderBoundY(other, bottomT);

    } else if (topT < bottomO && topO < topT && freeTop) { //object collide from above
         borderBoundY(other, topT - other->height);
    }

    if (rightT > leftO && rightO > rightT && freeRight) { //object collide from right
         borderBoundX(other, rightT);

    } else if (leftT < rightO && leftO < leftT && freeLeft) { // object collide from left
         borderBoundX(other, leftT - other->width);
    }


}

void TerrainCollisionComponent::onBorderCollision() {

}

void TerrainCollisionComponent::borderBoundX(Entity* other, float boundValue) {
    other->x = boundValue;
    other->xVelocity = 0.0f;
    other->collision->onBorderCollision();
}

void TerrainCollisionComponent::borderBoundY(Entity* other, float boundValue) {
    other->y = boundValue;
    other->yVelocity = 0.0f;
    other->collision->onBorderCollision();
}
