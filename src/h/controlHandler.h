#ifndef CORNERGAME_CONTROL_HANDLER_H
#define CORNERGAME_CONTROL_HANDLER_H

#include "command.h"
#include <list>

class ControlHandler {
private:
    std::list<Command*>& commandList;
public:
    ControlHandler(std::list<Command*>& commandList);
    int handleStateCommands();
};

#endif
