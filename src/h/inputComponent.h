#ifndef CORNERGAME_INPUT_COMPONENT_H
#define CORNERGAME_INPUT_COMPONENT_H

#include <SDL_keycode.h>
#include <map>
#include "command.h"

class Command;          // forward declared for circular dependency

class InputComponent {
public:
    std::map<SDL_Keycode, Command *> onKeyDownMap;

    InputComponent();
    ~InputComponent();

    void insertKeyDown(SDL_Keycode keycode, Command * command);
};

#endif //CORNERGAME_INPUT_COMPONENT_H
