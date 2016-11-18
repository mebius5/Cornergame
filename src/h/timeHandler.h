#ifndef CORNERGAME_TIME_HANDLER_H
#define CORNERGAME_TIME_HANDLER_H

#include <vector>
#include "consts.h"
#include "command.h"

class TimeHandler {
private:
    std::vector<Command*>& commandList;
    Command* lowerVolumeCommand;
    Command* raiseVolumeCommand;
    int frozenTime;
    bool slowMotion;
    int remainder;
public:
    TimeHandler(std::vector<Command*>& commandList);
    ~TimeHandler();
    int forward(int dt);
    void stopSlowMotion();
    void handleTimeCommands();
};

#endif
