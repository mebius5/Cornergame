#include "locationHandler.h"

LocationHandler::LocationHandler(std::list<Command*>& cmdList) :
        commandList(cmdList) {
}

//TODO: smooth out movement here
void LocationHandler::handleLocationCommands() {
    std::list<Command*>::const_iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end(); ++it) {
        Command* c = *it;
        if (MoveDownCommand* dCmd = dynamic_cast<MoveDownCommand*>(c)) {
            dCmd->entity->location->y += 1;
            it = this->commandList.erase(it);
            --it;
        } else if (MoveUpCommand* uCmd = dynamic_cast<MoveUpCommand*>(c)) {
            uCmd->entity->location->y -= 1;
            it = this->commandList.erase(it);
            --it;
        } else if (MoveLeftCommand* lCmd = dynamic_cast<MoveLeftCommand*>(c)) {
            lCmd->entity->location->x -= 1;
            it = this->commandList.erase(it);
            --it;
        } else if (MoveRightCommand* rCmd = dynamic_cast<MoveRightCommand*>(c)){
            rCmd->entity->location->x += 1;
            it = this->commandList.erase(it);
            --it;
        }
    }
}
