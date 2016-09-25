#ifndef CORNERGAME_LOCATION_HANDLER_H
#define CORNERGAME_LOCATION_HANDLER_H

#include <list>
#include <math.h>
#include "command.h"

class LocationHandler {
private:
    std::list<Command*>& commandList;
    float prevTime;             // records last time commands were handled
public:
    LocationHandler(std::list<Command*>& cmdList);
    void handleLocationCommands(float time);
};

#endif //CORNERGAME_LOCATION_HANDLER_H
