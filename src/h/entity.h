#ifndef CORNERGAME_ENTITY_H
#define CORNERGAME_ENTITY_H

#include "artComponent.h"
#include "inputComponent.h"
#include "locationComponent.h"
#include "physicsComponent.h"
#include "statsComponent.h"
#include "movementComponent.h"

class InputComponent;   // forward declared for circular dependency
class MovementComponent;

class Entity {
private:
    int id;
public:
    LocationComponent* location;
    StatsComponent* stats;
    PhysicsComponent* physics;
    ArtComponent* art;
    InputComponent* input;
    MovementComponent * movement;


    Entity(int id);
    ~Entity();
    int getId();
};

#endif //CORNERGAME_ENTITY_H
