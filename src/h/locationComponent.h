#ifndef CORNERGAME_LOCATION_COMPONENT_H
#define CORNERGAME_LOCATION_COMPONENT_H

#include "command.h"

class Command;          // forward declared for circular dependency

class LocationComponent {
public:
    float x;
    float y;
    int width;
    int height;
    Command* onEntityCollision;
    Command* onBorderCollision;

    LocationComponent(int x, int y, int width, int height,
                      Command* entityCollisionCmd, Command* borderCollisionCmd);
    ~LocationComponent();
};

#endif //CORNERGAME_LOCATION_COMPONENT_H
