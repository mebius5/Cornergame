#ifndef CORNERGAME_COLLISION_COMPONENT_H
#define CORNERGAME_COLLISION_COMPONENT_H

#include "entity.h"
#include "component.h"

class CollisionComponent : public Component {
public:
    CollisionComponent(Entity* entity);
    virtual ~CollisionComponent() { };

    virtual Command* onEntityCollision(Entity* other) = 0;
    virtual Command* onBorderCollision() = 0;
};

class HeroCollisionComponent : public CollisionComponent {
private:
    Command* entityCollisionCommand;
public:
    HeroCollisionComponent(Entity* entity, Command* entityCollisionCmd);
    ~HeroCollisionComponent();

    Command* onEntityCollision(Entity* other);
    Command* onBorderCollision();
};

class EnemyCollisionComponent : public CollisionComponent {
public:
    EnemyCollisionComponent(Entity* entity);
    Command* onEntityCollision(Entity* other);
    Command* onBorderCollision();
};

#endif
