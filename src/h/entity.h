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

#include "artComponent.h"
#include "inputComponent.h"
#include "collisionComponent.h"
#include "physicsComponent.h"
#include "scoreComponent.h"
#include "aiComponent.h"
#include "healthComponent.h"
#include "powerUpComponent.h"
#include "ammoComponent.h"

enum Action {IDLE, JUMP, THROW, DAMAGE, SLIDING};

class Entity {
private:
    int id;
public:
    float x;                    // coordinates of top left corner
    float y;
    int width;
    int height;
    int drawWidth;
    int drawHeight;
    int dir;
    Action actionState;
    bool rotates;

    CollisionComponent* collision;
    ScoreComponent* score;
    PhysicsComponent* physics;
    ArtComponent* art;
    InputComponent* input;
    AiComponent* ai;
    HealthComponent* health;
    PowerUpComponent * powerUp;
    AmmoComponent * ammo;

    Entity(int id, float x, float y, int w, int h, int drawWidth, int drawHeight);
    ~Entity();
    int getId();
};

#endif
