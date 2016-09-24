#ifndef CORNERGAME_LOCATION_HANDLER_H
#define CORNERGAME_LOCATION_HANDLER_H

#include <list>
#include "command.h"

class LocationHandler {

public:
    LocationHandler();
    void handleLocationCommands(std::list<Command *> commandList);
};

#endif //CORNERGAME_LOCATION_HANDLER_H
