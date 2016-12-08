#ifndef CORNERGAME_ENTITY_H
#define CORNERGAME_ENTITY_H

class CollisionComponent;         // forward declared for circular dependency
class DynamicCollisionComponent;
class AiComponent;
class InputComponent;
class ArtComponent;
class ScoreComponent;
class HealthComponent;
class PhysicsComponent;
class PowerUpComponent;
class AmmoComponent;
class ParticleComponent;

#include "artComponent.h"
#include "inputComponent.h"
#include "collisionComponent.h"
#include "physicsComponent.h"
#include "scoreComponent.h"
#include "aiComponent.h"
#include "healthComponent.h"
#include "powerUpComponent.h"
#include "ammoComponent.h"
#include "particleComponent.h"

class Entity {
protected:
    int id;
public:
    float x;                    // coordinates of top left corner
    float y;
    float drawX;
    float drawY;
    int width;
    int height;
    int drawWidth;
    int drawHeight;
    int dir;                    // direction player is facing (1 or -1)
    ActionEnum actionState;
    bool rotates;

    CollisionComponent* collision;
    ScoreComponent* score;
    PhysicsComponent* physics;
    ArtComponent* art;
    InputComponent* input;
    AiComponent* ai;
    HealthComponent* health;
    PowerUpComponent* powerUp;
    AmmoComponent* ammo;
    ParticleComponent* particle;

    Entity(int id, float x, float y, int w, int h, int drawWidth, int drawHeight);
    virtual ~Entity();
    virtual int getId();
    virtual void validate();
    virtual void invalidate();
};

class RespawnEntity : public Entity {
public:
    float initialX;
    float initialY;
    bool shifted;

    RespawnEntity(int id, float x, float y, int w, int h, int drawWidth, int drawHeight);
};

#endif
