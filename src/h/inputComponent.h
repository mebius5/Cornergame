#ifndef CORNERGAME_INPUT_COMPONENT_H
#define CORNERGAME_INPUT_COMPONENT_H

#include <SDL_keycode.h>
#include <map>
#include "command.h"

class Command;          // forward declared for circular dependency

class InputComponent {
public:
    std::map<SDL_Keycode, Command*> onKeyDown;
    float speed;

    InputComponent(float speed);
    ~InputComponent();

    void insertKeyDown(SDL_Keycode keycode, Command* command);
    Command* getKeyDownCmd(SDL_Keycode);
};

#endif //CORNERGAME_INPUT_COMPONENT_H
