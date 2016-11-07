#ifndef CORNERGAME_COLLISION_COMPONENT_H
#define CORNERGAME_COLLISION_COMPONENT_H

#include "entity.h"
#include "component.h"

class DynamicCollisionComponent;

class CollisionComponent : public Component {
public:
    CollisionComponent(Entity* entity);
    virtual ~CollisionComponent() { };

    virtual void onEntityCollision(DynamicCollisionComponent* otherComp) = 0;
    virtual void onBorderCollision() = 0;
    int sign(float x);
};

class StaticCollisionComponent : public CollisionComponent {
public:
    //int xBinIndex;
    //int yBinIndex;
    StaticCollisionComponent(Entity* entity);
};

class DynamicCollisionComponent : public CollisionComponent {
public:
    bool onGround;      // flags for whether the entity is on certain surfaces
    bool onLeftWall;    // onLeftWall means wall is on the left of the Entity
    bool onRightWall;
    int topBound;       // if onWall == true, these are the bounds of the wall
    int bottomBound;
    int leftBound;      // if onGround == true, these are the bounds of the platform
    int rightBound;
    DynamicCollisionComponent(Entity* entity);
    virtual void onStaticCollision(StaticCollisionComponent* otherComp) = 0;
};

class HeroCollisionComponent : public DynamicCollisionComponent {
private:
    Command* projCollisionCommand;
    Command* cameraShakeCommand;
public:
    HeroCollisionComponent(Entity* entity, Command* entityCollisionCmd);
    ~HeroCollisionComponent();

    void onEntityCollision(DynamicCollisionComponent* otherComp);
    void onStaticCollision(StaticCollisionComponent* otherComp);
    void onBorderCollision();
};

class EnemyCollisionComponent : public DynamicCollisionComponent {
public:
    EnemyCollisionComponent(Entity* entity);
    Command* projCollisionCommand;
    void onEntityCollision(DynamicCollisionComponent* otherComp);
    void onStaticCollision(StaticCollisionComponent* otherComp);
    void onBorderCollision();
};

class ProjectileCollisionComponent : public DynamicCollisionComponent {
private:
    Command* entityCollisionCommand;
public:
    int ownerID;
    ProjectileCollisionComponent(Entity* entity, Command* entCollisionCmd, int ownerID);
    ~ProjectileCollisionComponent();
    void onEntityCollision(DynamicCollisionComponent* otherComp);
    void onStaticCollision(StaticCollisionComponent* otherComp);
    void onBorderCollision();
};

class VictoryZoneCollisionComponent : public StaticCollisionComponent {
private:
    Command* entityCollisionCommand;
public:
    VictoryZoneCollisionComponent(Entity* entity, Command* entityCollisionCmd);
    ~VictoryZoneCollisionComponent();

    void onEntityCollision(DynamicCollisionComponent* otherComp);
    void onBorderCollision();
};

class TerrainCollisionComponent : public StaticCollisionComponent {
private:
    bool freeTop;
    bool freeBot;
    bool freeRight;
    bool freeLeft;
    void boundX(DynamicCollisionComponent* otherComp, float boundValue);
    void boundY(DynamicCollisionComponent* otherComp, float boundValue);
    void collideLeftWall(DynamicCollisionComponent* otherComp, float boundValue, int topT, int bottomT);
    void collideRightWall(DynamicCollisionComponent* otherComp, float boundValue, int topT, int bottomT);
    void collideGround(DynamicCollisionComponent* otherComp, float boundValue, int leftT, int rightT);
public:
    TerrainCollisionComponent(Entity* entity, bool top, bool bot, bool r, bool l);
    void onEntityCollision(DynamicCollisionComponent* otherComp);
    void onBorderCollision();
};

class PowerUpCollisionComponent : public StaticCollisionComponent {
protected:
    bool isClaimed;
    TextureEnum pwrUpType;
public:
    PowerUpCollisionComponent(Entity* entity, TextureEnum pwrUpType);
    void onEntityCollision(DynamicCollisionComponent* otherComp);
    void onBorderCollision();
    void setIsClaimed(bool isClaimed);
};

#endif
