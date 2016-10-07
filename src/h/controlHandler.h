#ifndef CORNERGAME_CONTROL_HANDLER_H
#define CORNERGAME_CONTROL_HANDLER_H

#include <vector>
#include "enums.h"
#include "command.h"

class ControlHandler {
private:
    std::vector<Command*>& commandList;
public:
    ControlHandler(std::vector<Command*>& commandList);
    StateEnum handleStateCommands();
};

#endif
