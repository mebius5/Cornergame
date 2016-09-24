#ifndef CORNERGAME_COLLISION_HANDLER_H
#define CORNERGAME_COLLISION_HANDLER_H

#include "command.h"
#include <iostream>


class CollisionHandler {
private:
    std::map<int, Entity *> & entityMap;
    std::list<Command *> & commandList;
public:
    CollisionHandler(std::map<int, Entity *> & entityMap, std::list<Command*> & commandList);
    void handleCollision();
    bool isRectOverlapping(LocationComponent * a, LocationComponent * b);
};

#endif //CORNERGAME_COLLISION_HANDLER_H
