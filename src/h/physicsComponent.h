#ifndef CORNERGAME_PHYSICS_COMPONENT_H
#define CORNERGAME_PHYSICS_COMPONENT_H

#include "entity.h"
#include "component.h"

class PhysicsComponent : public Component {
private:
    //float minVelocity;
    Command* jumpCommand;
    Command* startSlideCommand;
    Command* stopSlideCommand;
    float xAccel;
    float yAccel;
    float accelAmount;
    float gravity;
    float slideVelocity;
    int jumps;
    bool infiniteJumps;
    DynamicCollisionComponent* collisionComp;
    float clipVelocity(float velocity, float max);

public:
    float xVelocity;
    float yVelocity;
    float maxXVelocity;
    float maxYVelocity;
    float jumpVelocity;
    float deceleration;
    int maxJumps;
    Entity * target;
    float rotSpeed;

    PhysicsComponent(Entity* entity);
    ~PhysicsComponent();

    void updateLocation(int dt);
    void jump();
    void toggleInfiniteJumps();
    bool isInfiniteJumpOn();
    void resetJumps();
    void bump(int dir);
    void accelerateX(int dir);
    void accelerateY(int dir);
    void clearAccelerationX();
    void clearAccelerationY();
};

#endif
