#include <movementHandler.h>

MovementHandler::MovementHandler(std::map < int, Entity * > & entityMap,
                           std::list<Command *> & commandList):
        entityMap(entityMap), commandList(commandList) {
}

void MovementHandler::handleMovement() {

    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        if(it ->second->movement){
            std::list<Command * > & movement = it -> second->movement->movementList;
            std::list<Command *>::const_iterator iterator;
            for(iterator = movement.begin(); iterator != movement.end(); ++iterator){
                commandList.push_back(*iterator);
            }
        }
    }
}