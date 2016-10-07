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
    bool valid;
public:
    Entity* entity;
    Component(Entity* entity);
    virtual ~Component() { };
    void invalidate();
    bool isValid();
    static void setCommandList(std::list<Command*>* commandListPtr);
};

#endif
