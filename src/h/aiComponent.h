#ifndef CORNERGAME_AI_COMPONENT_H
#define CORNERGAME_AI_COMPONENT_H

#include <vector>
#include <math.h>
#include "command.h"

class Command;          // forward declared for circular dependency

class AiComponent {
private:
    std::vector<Command*> commands;
    float lastGenTime;          // last time a command was generated
    Command* lastGenCommand;    // last command that was generated
public:
    AiComponent();
    ~AiComponent();

    void newBehavior(Command* command);
    Command* generateBehavior(float time);
    void resetTimer();
};

#endif //CORNERGAME_AI_COMPONENT_H
