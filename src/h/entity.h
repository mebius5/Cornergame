#ifndef CORNERGAME_ENTITY_H
#define CORNERGAME_ENTITY_H

#include "artComponent.h"
#include "inputComponent.h"
#include "collisionComponent.h"
#include "physicsComponent.h"
#include "scoreComponent.h"
#include "aiComponent.h"

class CollisionComponent;       // forward declared for circular dependency
class AiComponent;
class InputComponent;
class ArtComponent;
class ScoreComponent;

class Entity {
private:
    int id;
public:
    float x;                    // coordinates of top left corner
    float y;
    int width;
    int height;
    float xVelocity;
    float yVelocity;
    float xAccel;
    float yAccel;

    CollisionComponent* collision;
    ScoreComponent* score;
    PhysicsComponent* physics;
    ArtComponent* art;
    InputComponent* input;
    AiComponent* ai;

    Entity(int id, float x, float y, int w, int h);
    ~Entity();
    int getId();
};

#endif
