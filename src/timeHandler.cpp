#include "timeHandler.h"
#include <iostream>

TimeHandler::TimeHandler(std::vector<Command*>& commandList) :
    commandList(commandList),
    lowerVolumeCommand(new LowerVolumeCommand()),
    raiseVolumeCommand(new RaiseVolumeCommand()),
    frozenTime(0),
    slowMotion(false),
    remainder(0) {
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

        // keep track of remainder so we don't lose time
        remainder += dt % 4;
        if (remainder > 4) {
            dt += 4; // this cannot change the remainder
            remainder -= 4;
        }
        dt /= 4;

    // if no longer slow motion clear remainder for next time
    } else {
        remainder = 0;
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
        } else if (TimeSlowCommand* cmd = dynamic_cast<TimeSlowCommand*>(*it)) {
            if (cmd->valid) {
                this->slowMotion = true;
                this->commandList.push_back(this->lowerVolumeCommand);
            }
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
