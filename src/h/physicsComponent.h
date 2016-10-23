#ifndef CORNERGAME_PHYSICS_COMPONENT_H
#define CORNERGAME_PHYSICS_COMPONENT_H

#include "entity.h"
#include "component.h"

class PhysicsComponent : public Component {
private:
    //float minVelocity;
    float xAccel;
    float yAccel;
    float accelAmount;
    float gravity;
    int jumps;
    bool infiniteJumps;
    DynamicCollisionComponent* collisionComp;
    float clipVelocity(float velocity);

public:
    float xVelocity;
    float yVelocity;
    float maxVelocity;
    float jumpVelocity;
    float deceleration;
    int maxJumps;

    PhysicsComponent(Entity* entity);
    ~PhysicsComponent();

    void updateLocation(int dt);
    void jump();
    void toggleInfiniteJumps();
    void resetJumps();
    void bump(int dir);
    void accelerateX(int dir);
    void accelerateY(int dir);
    void clearAccelerationX();
    void clearAccelerationY();
};

#endif
