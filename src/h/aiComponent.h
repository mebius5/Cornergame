#ifndef CORNERGAME_AI_COMPONENT_H
#define CORNERGAME_AI_COMPONENT_H

#include <vector>
#include <command.h>

class Command;          // forward declared for circular dependency
class Entity;

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
};

#endif //CORNERGAME_AI_COMPONENT_H
