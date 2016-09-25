#include "locationHandler.h"

#define TWO_PI 2 * M_PI


LocationHandler::LocationHandler(std::list<Command*>& cmdList) :
        commandList(cmdList) {
    this->prevTime = 0;
}

void LocationHandler::handleLocationCommands(int rawtime) {
    int timeDiff = rawtime - this->prevTime;
    this->prevTime = rawtime;

    std::list<Command*>::const_iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end(); ) {
        Command* c = *it;
        float speed;
        if (MoveDownCommand* dCmd = dynamic_cast<MoveDownCommand*>(c)) {
            speed = this->getSpeed(dCmd->entity);
            dCmd->entity->location->y += timeDiff * speed;
            it = this->commandList.erase(it);
        } else if (MoveUpCommand* uCmd = dynamic_cast<MoveUpCommand*>(c)) {
            speed = this->getSpeed(uCmd->entity);
            uCmd->entity->location->y -= timeDiff * speed;
            it = this->commandList.erase(it);
        } else if (MoveLeftCommand* lCmd = dynamic_cast<MoveLeftCommand*>(c)) {
            speed = this->getSpeed(lCmd->entity);
            lCmd->entity->location->x -= timeDiff * speed;
            it = this->commandList.erase(it);
        } else if (MoveRightCommand* rCmd = dynamic_cast<MoveRightCommand*>(c)){
            speed = this->getSpeed(rCmd->entity);
            rCmd->entity->location->x += timeDiff * speed;
            it = this->commandList.erase(it);
        } else {
            ++it;
        }
    }
}

float LocationHandler::getSpeed(Entity* entity) {
    if (entity->ai)
        return entity->ai->speed;
    else if (entity->input)
        return entity->input->speed;
    else
        return 0.0f;
}
