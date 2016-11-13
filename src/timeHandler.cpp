#include "timeHandler.h"

TimeHandler::TimeHandler(std::vector<Command*>& commandList) :
    commandList(commandList),
    lowerVolumeCommand(new LowerVolumeCommand()),
    raiseVolumeCommand(new RaiseVolumeCommand()),
    frozenTime(0),
    slowMotion(false) {
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
        // never let dt = 0 or else we're screwed
        if (dt == 0) {
            dt = 1;
        }
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
