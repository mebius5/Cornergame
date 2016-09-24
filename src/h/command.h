#ifndef CORNERGAME_COMMAND_H
#define CORNERGAME_COMMAND_H

#include "entity.h"

class Entity;           // forward declared for circular dependency

class Command {
public:
    int id;
};

// A command to be handled by the location calculator
class LocationCommand : public Command {

};

class MoveLeftCommand : public LocationCommand {
    Entity* entity;     // the entity to move
};

class MoveRightCommand : public LocationCommand {
    Entity* entity;
};

#endif //CORNERGAME_COMMAND_H
