#ifndef CORNERGAME_MOVEMENT_COMPONENT_H
#define CORNERGAME_MOVEMENT_COMPONENT_H

#include "entity.h"
#include "component.h"
#include <cmath>

class MovementComponent : public PhysicsComponent {
public:
    MovementComponent(Entity* entity);
    void updateLocation(int dt);
};

#endif
