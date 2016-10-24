#ifndef CORNERGAME_INPUT_HANDLER_H
#define CORNERGAME_INPUT_HANDLER_H

#include <SDL.h>
#include <SDL_events.h>
#include <vector>
#include "entity.h"

class InputHandler {
protected:
    std::vector<InputComponent*>& componentList;
    std::vector<Command*>& commandList;
    SwitchStateCommand quitCommand;
    SwitchStateCommand switchToMenu;
    SwitchStateCommand previewOff;
public:
    InputHandler(std::vector<InputComponent*>& componentList,
                 std::vector<Command*>& commandList);
    virtual void handleEvents();
};

#endif
