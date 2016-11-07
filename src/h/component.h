#ifndef CORNERGAME_COMPONENT_H
#define CORNERGAME_COMPONENT_H

#include <vector>
#include "entity.h"
#include "command.h"

class Entity;
class Command;

class Component {
protected:
    static std::vector<Command*>* commandList;
    bool valid;
public:
    Entity* entity;
    Component(Entity* entity);
    virtual ~Component() { };
    void validate();
    void invalidate();
    bool isValid();
    static void setCommandList(std::vector<Command*>* commandListPtr);
};

#endif
