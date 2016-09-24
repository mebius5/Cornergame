#ifndef CORNERGAME_ENTITY_H
#define CORNERGAME_ENTITY_H

#include "artComponent.h"
#include "inputComponent.h"
#include "locationComponent.h"
#include "physicsComponent.h"
#include "statsComponent.h"

class InputComponent;   // forward declared for circular dependency

class Entity {
private:
    int id;
public:
    LocationComponent* location;
    StatsComponent* stats;
    PhysicsComponent* physics;
    ArtComponent* art;
    InputComponent* input;

    Entity();
    ~Entity();
};

#endif //CORNERGAME_ENTITY_H
