#ifndef CORNERGAME_COMPONENT_H
#define CORNERGAME_COMPONENT_H

#include "entity.h"
#include "command.h"

class Entity;
class Command;

class Component {
public:
    Entity* entity;
    Component(Entity* entity);
    virtual ~Component() { };
    virtual void passCommand(Command* command);
};

#endif
