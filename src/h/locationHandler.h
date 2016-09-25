#ifndef CORNERGAME_LOCATION_HANDLER_H
#define CORNERGAME_LOCATION_HANDLER_H

#include <list>
#include "command.h"

class LocationHandler {
private:
    std::list<Command*>& commandList;
public:
    LocationHandler(std::list<Command*>& cmdList);
    void handleLocationCommands();
};

#endif //CORNERGAME_LOCATION_HANDLER_H
