#include "locationComponent.h"

LocationComponent::LocationComponent(int x, int y, int width, int height,
                                     Command* entityCollisionCmd,
                                     Command* borderCollisionCmd) :
        x(x),
        y(y),
        width(width),
        height(height),
        onEntityCollision(entityCollisionCmd),
        onBorderCollision(borderCollisionCmd) {
}

LocationComponent::~LocationComponent() {
    if (this->onEntityCollision)
        delete this->onEntityCollision;
    if (this->onBorderCollision)
        delete this->onBorderCollision;
}
