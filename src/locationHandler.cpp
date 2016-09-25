#include "locationHandler.h"

#define TWO_PI 2 * M_PI


LocationHandler::LocationHandler(std::list<Command*>& cmdList) :
        commandList(cmdList) {
    this->prevTime = 0.0f;
}

//TODO: smooth out movement here
void LocationHandler::handleLocationCommands(float time) {
    float timeDiff = time - this->prevTime;
    if (timeDiff < 0)
        timeDiff += TWO_PI;
    this->prevTime = time;
    std::list<Command*>::const_iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end(); ) {
        Command* c = *it;
        if (MoveDownCommand* dCmd = dynamic_cast<MoveDownCommand*>(c)) {
            dCmd->entity->location->y += 500 * timeDiff;
            it = this->commandList.erase(it);
        } else if (MoveUpCommand* uCmd = dynamic_cast<MoveUpCommand*>(c)) {
            uCmd->entity->location->y -= 500 * timeDiff;
            it = this->commandList.erase(it);
        } else if (MoveLeftCommand* lCmd = dynamic_cast<MoveLeftCommand*>(c)) {
            lCmd->entity->location->x -= 500 * timeDiff;
            it = this->commandList.erase(it);
        } else if (MoveRightCommand* rCmd = dynamic_cast<MoveRightCommand*>(c)){
            rCmd->entity->location->x += 500 * timeDiff;
            it = this->commandList.erase(it);
        } else {
            ++it;
        }
    }
}
