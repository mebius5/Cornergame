#ifndef CORNERGAME_INPUT_COMPONENT_H
#define CORNERGAME_INPUT_COMPONENT_H

#include "command.h"

class Command;          // forward declared for circular dependency

class InputComponent {
public:
    Command* onLeft;
    Command* onRight;
    Command* onUp;
    Command* onDown;

    InputComponent();
    ~InputComponent();
};

#endif //CORNERGAME_INPUT_COMPONENT_H
