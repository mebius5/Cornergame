#ifndef CORNERGAME_PHYSICS_COMPONENT_H
#define CORNERGAME_PHYSICS_COMPONENT_H

#include "entity.h"
#include "component.h"
#include <cmath>

class PhysicsComponent : public Component {
private:
    //float minVelocity;
    Command* jumpCommand;
    Command* startSlideCommand;
    Command* stopSlideCommand;
    Command* timeSlowCommand;
    Command* timeNormalCommand;
    float xAccel;
    float yAccel;
    float accelAmount;
    float gravity;
    float slideVelocity;
    int jumps;
    bool infiniteJumps;
    bool frozen;
    bool slow;
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
    int dodgeTime;
    Entity * target;
    float rotSpeed;

    PhysicsComponent(Entity* entity);
    ~PhysicsComponent();

    void updateLocation(int dt);
    void freeze();
    bool isFrozen();
    void jump(float velocity = -1);
    void toggleInfiniteJumps();
    bool isInfiniteJumpOn();
    void resetJumps();
    void bump(int dir);
    void dodge(int dir);
    void accelerateX(int dir);
    void accelerateY(int dir);
    void clearAccelerationX();
    void clearAccelerationY();
};

#endif
