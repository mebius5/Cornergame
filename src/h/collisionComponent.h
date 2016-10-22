#ifndef CORNERGAME_COLLISION_COMPONENT_H
#define CORNERGAME_COLLISION_COMPONENT_H

#include "entity.h"
#include "component.h"

class CollisionComponent : public Component {
public:
    CollisionComponent(Entity* entity);
    virtual ~CollisionComponent() { };

    virtual void onEntityCollision(Entity* other, int dt) = 0;
    virtual void onBorderCollision() = 0;
};

class StaticCollisionComponent : public CollisionComponent {
public:
    //int xBinIndex;
    //int yBinIndex;
    StaticCollisionComponent(Entity* entity);
};

class DynamicCollisionComponent : public CollisionComponent {
public:
    bool onGround;
    bool onLeftWall;
    bool onRightWall;
    DynamicCollisionComponent(Entity* entity);
    virtual void onStaticCollision(Entity* other) = 0;
};

class HeroCollisionComponent : public DynamicCollisionComponent {
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

class EnemyCollisionComponent : public DynamicCollisionComponent {
public:
    EnemyCollisionComponent(Entity* entity);
    void onEntityCollision(Entity *other, int dt);
    void onStaticCollision(Entity *other);
    void onBorderCollision();
};

class ProjectileCollisionComponent : public DynamicCollisionComponent {
private:
    Command* entityCollisionCommand;
public:
    int ownerID;
    ProjectileCollisionComponent(Entity* entity, Command* entCollisionCmd, int ownerID);
    ~ProjectileCollisionComponent();
    void onEntityCollision(Entity *other, int dt);
    void onStaticCollision(Entity *other);
    void onBorderCollision();
};

class VictoryZoneCollisionComponent : public StaticCollisionComponent {
private:
    Command* entityCollisionCommand;
public:
    VictoryZoneCollisionComponent(Entity* entity, Command* entityCollisionCmd);
    ~VictoryZoneCollisionComponent();

    void onEntityCollision(Entity *other, int dt);
    void onBorderCollision();
};

class TerrainCollisionComponent : public StaticCollisionComponent {
private:
    bool freeTop;
    bool freeBot;
    bool freeRight;
    bool freeLeft;
    void borderBoundX(Entity* other, float boundValue);
    void borderBoundY(Entity* other, float boundValue);
public:
    TerrainCollisionComponent(Entity* entity, bool top, bool bot, bool r, bool l);
    void onEntityCollision(Entity *other, int dt);
    void onBorderCollision();
};

#endif
