#include "locationComponent.h"

LocationComponent::LocationComponent(int x, int y, int width, int height,
                                     Command* onCollision) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->onCollision = onCollision;
}

LocationComponent::~LocationComponent() {
    delete this->onCollision;
}
