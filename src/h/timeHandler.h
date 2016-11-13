#ifndef CORNERGAME_TIME_HANDLER_H
#define CORNERGAME_TIME_HANDLER_H

#include <vector>
#include "enums.h"
#include "command.h"

class TimeHandler {
private:
    std::vector<Command*>& commandList;
    Command* lowerVolumeCommand;
    Command* raiseVolumeCommand;
    int frozenTime;
    bool slowMotion;
public:
    TimeHandler(std::vector<Command*>& commandList);
    ~TimeHandler();
    int forward(int dt);
    void stopSlowMotion();
    void handleTimeCommands();
};

#endif
