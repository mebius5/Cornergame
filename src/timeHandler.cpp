#include "timeHandler.h"
#include <iostream>

TimeHandler::TimeHandler(std::vector<Command*>& commandList) :
    commandList(commandList),
    lowerVolumeCommand(new LowerVolumeCommand()),
    raiseVolumeCommand(new RaiseVolumeCommand()),
    frozenTime(0),
    slowMotion(false) {
}

TimeHandler::~TimeHandler() {
    if(lowerVolumeCommand){
        delete this->lowerVolumeCommand;
    }
    if(raiseVolumeCommand){
        delete this->raiseVolumeCommand;
    }
}

int TimeHandler::forward(int dt) {

    // if there is still time to be frozen
    if (this->frozenTime > dt) {
        this->frozenTime -= dt;
        dt = 0;

    // if we are done being frozen
    } else {
        dt -= this->frozenTime;
        this->frozenTime = 0;
    }

    // handle slow motion
    if (this->slowMotion) {
        dt /= 4;
        if (dt == 0) {
            dt = 1;
        }
        // never let dt = 0 or else we're screwed
       
    }

    return dt;
}

void TimeHandler::stopSlowMotion() {
    this->slowMotion = false;
}

void TimeHandler::handleTimeCommands() {
    std::vector<Command*>::iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end(); ) {
        if (TimeFreezeCommand* timeCmd = dynamic_cast<TimeFreezeCommand*>(*it)) {
            this->frozenTime += timeCmd->time;
        } else if (dynamic_cast<TimeSlowCommand*>(*it)) {
            this->slowMotion = true;
            this->commandList.push_back(this->lowerVolumeCommand);
        } else if (dynamic_cast<TimeNormalCommand*>(*it)) {
            this->slowMotion = false;
            this->commandList.push_back(this->raiseVolumeCommand);
        } else {
            ++it;
            continue;
        }

        *it = this->commandList.back();
        this->commandList.pop_back();
    }
}
