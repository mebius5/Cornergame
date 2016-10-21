#ifndef CORNERGAME_COLLISION_COMPONENT_H
#define CORNERGAME_COLLISION_COMPONENT_H

#include "entity.h"
#include "component.h"

class CollisionComponent : public Component {
public:
    bool staticObject;
    CollisionComponent(Entity* entity, bool staticObject);
    virtual ~CollisionComponent() { };

    virtual void onEntityCollision(Entity *other, int dt) = 0;
    virtual void onStaticCollision(Entity *other) = 0;
    virtual void onBorderCollision() = 0;
};

class HeroCollisionComponent : public CollisionComponent {
private:
    Command* entityCollisionCommand;
    int timeSinceLastCollision;
public:
    HeroCollisionComponent(Entity* entity, Command* entityCollisionCmd);
    ~HeroCollisionComponent();

    void onEntityCollision(Entity *other, int dt);
    void onStaticCollision(Entity *other);
    void onBorderCollision();
};

class EnemyCollisionComponent : public CollisionComponent {
public:
    EnemyCollisionComponent(Entity* entity);
    void onEntityCollision(Entity *other, int dt);
    void onStaticCollision(Entity *other);
    void onBorderCollision();
};

class ProjectileCollisionComponent : public CollisionComponent {
private:
    Command* entityCollisionCommand;
public:
    int ownerID;
    ProjectileCollisionComponent(Entity* entity, Command* entityCollisionCommand, int ownerID);
    void onEntityCollision(Entity *other, int dt);
    void onStaticCollision(Entity *other);
    void onBorderCollision();
};

class VictoryZoneCollisionComponent : public CollisionComponent {
private:
    Command* entityCollisionCommand;
public:
    VictoryZoneCollisionComponent(Entity* entity, Command* entityCollisionCmd);
    ~VictoryZoneCollisionComponent();

    void onEntityCollision(Entity *other, int dt);
    void onStaticCollision(Entity *other);
    void onBorderCollision();
};

class TerrainCollisionComponent : public CollisionComponent {
private:
    void borderBoundX(Entity* other, float boundValue);
    void borderBoundY(Entity* other, float boundValue);
    bool freeTop;
    bool freeBot;
    bool freeRight;
    bool freeLeft;
public:
    TerrainCollisionComponent(Entity * entity, bool freeTop, bool freeBot, bool freeRight, bool freeLeft);
    void onEntityCollision(Entity *other, int dt);
    void onStaticCollision(Entity *other);
    void onBorderCollision();
};

#endif
