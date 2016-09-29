#ifndef CORNERGAME_COLLISION_COMPONENT_H
#define CORNERGAME_COLLISION_COMPONENT_H

#include "command.h"

class Command;          // forward declared for circular dependency

class CollisionComponent {
public:
    Command* onEntityCollision;
    Command* onBorderCollision;

    CollisionComponent(Command* onEntityCollision, Command* onBorderCollision);
    ~CollisionComponent();
};

#endif
