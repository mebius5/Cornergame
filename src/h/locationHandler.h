#ifndef CORNERGAME_LOCATION_HANDLER_H
#define CORNERGAME_LOCATION_HANDLER_H

#include <list>
#include <math.h>
#include "command.h"

class LocationHandler {
private:
    std::list<Command*>& commandList;
    int prevTime;              // records last time commands were handled
    float getSpeed(Entity* entity);
public:
    LocationHandler(std::list<Command*>& cmdList);
    void handleLocationCommands(int rawtime);
};

#endif //CORNERGAME_LOCATION_HANDLER_H
