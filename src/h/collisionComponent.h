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
};

class EnemyCollisionComponent : public DynamicCollisionComponent {
public:
    EnemyCollisionComponent(Entity* entity);
    ~EnemyCollisionComponent();
    Command* projCollisionCommand;
    void onEntityCollision(DynamicCollisionComponent* otherComp);
    void onStaticCollision(StaticCollisionComponent* otherComp);
};

class ProjectileCollisionComponent : public DynamicCollisionComponent {
private:
    Command* despawnCommand;
    TimeFreezeCommand* timeFreezeCommand;
    TimeNormalCommand* timeNormalCommand;
public:
    int ownerID;
    ProjectileCollisionComponent(Entity* entity, Command* entCollisionCmd, int ownerID);
    ~ProjectileCollisionComponent();
    void onEntityCollision(DynamicCollisionComponent* otherComp);
    void onStaticCollision(StaticCollisionComponent* otherComp);
};

class BombCollisionComponent : public DynamicCollisionComponent {
private:
    bool exploded;
    Command* screenShakeCmd;
public:
    BombCollisionComponent(Entity* entity);
    ~BombCollisionComponent();
    void explode();
    void onEntityCollision(DynamicCollisionComponent* otherComp);
    void onStaticCollision(StaticCollisionComponent* otherComp);
};

class VictoryZoneCollisionComponent : public StaticCollisionComponent {
private:
    Command* entityCollisionCommand;
public:
    VictoryZoneCollisionComponent(Entity* entity, Command* entityCollisionCmd);
    ~VictoryZoneCollisionComponent();
    void onEntityCollision(DynamicCollisionComponent* otherComp);
};

class TerrainCollisionComponent : public StaticCollisionComponent {
protected:
    Command* landCommand;
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
    ~TerrainCollisionComponent();
    void onEntityCollision(DynamicCollisionComponent* otherComp);
};

class FadingTerrainColComponent : public TerrainCollisionComponent {
protected:
    bool hasDisappeared;
    bool touched;
    DynamicCollisionComponent * heroOtherComp1;
    DynamicCollisionComponent * heroOtherComp2;
public:
    FadingTerrainColComponent(Entity* entity, bool top, bool bot, bool r, bool l);
    void onEntityCollision(DynamicCollisionComponent* otherComp);
    void setHasDisappeared(bool hasDisappeared);
    void resetComponent();

};

class PowerUpCollisionComponent : public StaticCollisionComponent {
protected:
    Command* pickupCommand;
    bool isClaimed;
    TextureEnum pwrUpType;
public:
    PowerUpCollisionComponent(Entity* entity, TextureEnum pwrUpType, SfxEnum pwrSound);
    ~PowerUpCollisionComponent();
    void onEntityCollision(DynamicCollisionComponent* otherComp);
    void setIsClaimed(bool isClaimed);
};

class BounceCollisionComponent : public StaticCollisionComponent {
private:
    Command* bounceCommand;
    float bounceVelocity;
public:
    BounceCollisionComponent(Entity* entity);
    ~BounceCollisionComponent();
    void onEntityCollision(DynamicCollisionComponent* otherComp);
};

#endif
