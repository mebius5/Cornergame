#include "controlHandler.h"

ControlHandler::ControlHandler(std::vector<Command*>& commandList) :
    commandList(commandList) {
}

StateEnum ControlHandler::handleStateCommands() {
    std::vector<Command*>::iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end(); ++it) {
        if (SwitchStateCommand* ssCmd = dynamic_cast<SwitchStateCommand*>(*it)) {
            *it = this->commandList.back();
            this->commandList.pop_back();
            return ssCmd->newState;
        }
    }
    return STATE_NONE;
}

bool ControlHandler::isPreviewOff() {
    std::vector<Command*>::iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end(); ++it) {
        if (dynamic_cast<PreviewOffCommand*>(*it)) {
            *it = this->commandList.back();
            this->commandList.pop_back();
            return true;
        }
    }
    return false;
}