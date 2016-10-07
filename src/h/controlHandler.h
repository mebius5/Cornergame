#ifndef CORNERGAME_CONTROL_HANDLER_H
#define CORNERGAME_CONTROL_HANDLER_H

#include <list>
#include "enums.h"
#include "command.h"

class ControlHandler {
private:
    std::list<Command*>& commandList;
public:
    ControlHandler(std::list<Command*>& commandList);
    StateEnum handleStateCommands();
};

#endif
