#ifndef CORNERGAME_COLLISION_HANDLER_H
#define CORNERGAME_COLLISION_HANDLER_H

#include "command.h"
#include <locationComponent.h>
#include <iostream>


class CollisionHandler {
private:
    std::map<int, Entity *> & entityMap;
    std::list<Command *> & commandList;
    const int width;
    const int height;
    bool isRectOverlapping(LocationComponent * a, LocationComponent * b);
    void handleBorderCollision(Entity *entity);
public:
    CollisionHandler(std::map<int, Entity *> & entityMap, std::list<Command*> & commandList,
                     const int WIDTH, const int HEIGHT);
    void handleCollision();
};

#endif //CORNERGAME_COLLISION_HANDLER_H
