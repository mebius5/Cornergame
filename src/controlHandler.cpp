#include "controlHandler.h"

ControlHandler::ControlHandler(std::list<Command*>& commandList) :
    commandList(commandList) {
}

StateEnum ControlHandler::handleStateCommands() {
    std::list<Command*>::const_iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end(); ++it) {
        Command* c = *it;
        if (SwitchStateCommand* ssCmd = dynamic_cast<SwitchStateCommand*>(c)) {
            this->commandList.erase(it);
            return ssCmd->newState;
        }
    }
    return STATE_NONE;
}
