#ifndef CORNERGAME_COMPONENT_H
#define CORNERGAME_COMPONENT_H

#include "entity.h"
#include "command.h"

class Entity;
class Command;

class Component {
protected:
    Entity* entity;
public:
    Component(Entity* entity);
    virtual ~Component() { };
    virtual void passCommand(Command* command);
};

#endif
