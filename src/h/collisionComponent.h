#ifndef CORNERGAME_COLLISION_COMPONENT_H
#define CORNERGAME_COLLISION_COMPONENT_H

#include "entity.h"
#include "component.h"

class CollisionComponent : public Component {
public:
    CollisionComponent(Entity* entity);
    virtual ~CollisionComponent() { };

    virtual void onEntityCollision(Entity* other) = 0;
    virtual void onBorderCollision() = 0;
};

class HeroCollisionComponent : public CollisionComponent {
private:
    Command* entityCollisionCommand;
public:
    HeroCollisionComponent(Entity* entity, Command* entityCollisionCmd);
    ~HeroCollisionComponent();

    void onEntityCollision(Entity* other);
    void onBorderCollision();
};

class EnemyCollisionComponent : public CollisionComponent {
public:
    EnemyCollisionComponent(Entity* entity);
    void onEntityCollision(Entity* other);
    void onBorderCollision();
};

class VictoryZoneCollisionComponent : public CollisionComponent {
private:
    Command* entityCollisionCommand;
public:
    VictoryZoneCollisionComponent(Entity* entity, Command* entityCollisionCmd);
    ~VictoryZoneCollisionComponent();

    void onEntityCollision(Entity* other);
    void onBorderCollision();
};

#endif
