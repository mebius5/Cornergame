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
    HeroCollisionComponent(Command* entityCollCmd, Entity* entity);
    ~HeroCollisionComponent();

    Command* onEntityCollision(Entity* other);
    Command* onBorderCollision();
};

class EnemyCollisionComponent : public CollisionComponent {
private:
    Command* borderCollisionCommand;
public:
    EnemyCollisionComponent(Entity* entity, Command* borderCollCmd);
    ~EnemyCollisionComponent();

    Command* onEntityCollision(Entity* other);
    Command* onBorderCollision();
};

#endif
