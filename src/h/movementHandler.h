#ifndef CORNERGAME_MOVEMENTHANDLER_H
#define CORNERGAME_MOVEMENTHANDLER_H

#include "entity.h"

class MovementHandler {
private:
    std::map<int, Entity *> & entityMap;
    std::list<Command *> & commandList;

public:
    MovementHandler(std::map<int, Entity *> & entityMap, std::list<Command*> & commandList);
    void handleMovement ();
};

#endif //CORNERGAME_MOVEMENTHANDLER_H
