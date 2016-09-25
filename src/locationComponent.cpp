#include "locationComponent.h"

LocationComponent::LocationComponent(int x, int y, int width, int height,
                                     Command* entityCollisionCmd,
                                     Command* borderCollisionCmd) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->onEntityCollision = entityCollisionCmd;
    this->onBorderCollision = borderCollisionCmd;
}

LocationComponent::~LocationComponent() {
    if (this->onEntityCollision)
        delete this->onEntityCollision;
    if (this->onBorderCollision)
        delete this->onBorderCollision;
}
