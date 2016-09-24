

#ifndef CORNERGAME_MOVEMENTCOMPONENT_H
#define CORNERGAME_MOVEMENTCOMPONENT_H

#include <list>
#include <command.h>

class Command;          // forward declared for circular dependency
class Entity;

class MovementComponent {
public:
    std::list<Command *> movementList;

    MovementComponent();
    ~MovementComponent();

    void insertMovement(Command * command);
    //void insertRandomMovement(Entity * entity);
};

#endif //CORNERGAME_MOVEMENTCOMPONENT_H
