#ifndef CORNERGAME_COLLISION_HANDLER_H
#define CORNERGAME_COLLISION_HANDLER_H

#include "command.h"
#include <locationComponent.h>
#include <list>
#include <map>
#include <iterator>

class CollisionHandler {
private:
    std::map<int, Entity *> & entityMap;
    std::list<Command *> & commandList;
    const int width;
    const int height;
    bool isRectOverlapping(Entity* entity1, Entity* entity2);
    void handleBorderCollision(Entity *entity);
public:
    CollisionHandler(std::map<int, Entity *> & entityMap,
                     std::list<Command*> & commandList,
                     const int w, const int h);
    void handleCollision();
};

#endif //CORNERGAME_COLLISION_HANDLER_H
