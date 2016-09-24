#include "locationHandler.h"

LocationHandler::LocationHandler() {

}

void LocationHandler::handleLocationCommands(std::list<Command *> & commandList){

    std::list<Command *>::const_iterator it;
    for( it = commandList.begin(); it != commandList.end(); ++it){
        Command * command = *it;
        if(MoveDownCommand * moveDown = dynamic_cast<MoveDownCommand *> (command)){
            moveDown->entity->location->y+=1;
            commandList.erase(it);
        } else if (MoveUpCommand * moveUp = dynamic_cast<MoveUpCommand * > (command)){
            moveUp->entity->location->y-=1;
            commandList.erase(it);
        } else if (MoveLeftCommand * moveLeft = dynamic_cast<MoveLeftCommand * > (command)){
            moveLeft->entity->location->x-=1;
            commandList.erase(it);
        } else if (MoveRightCommand * moveRight = dynamic_cast<MoveRightCommand * > (command)){
            moveRight->entity->location->x+=1;
            commandList.erase(it);
        }
    }
}