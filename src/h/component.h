#ifndef CORNERGAME_COMPONENT_H
#define CORNERGAME_COMPONENT_H

#include <list>
#include "entity.h"
#include "command.h"

class Entity;
class Command;

class Component {
protected:
    static std::list<Command*>* commandList;
public:
    Entity* entity;
    Component(Entity* entity);
    virtual ~Component() { };
    static void setCommandList(std::list<Command*>* commandListPtr);
};

#endif
