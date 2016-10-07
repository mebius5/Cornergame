#ifndef CORNERGAME_INPUT_HANDLER_H
#define CORNERGAME_INPUT_HANDLER_H

#include <SDL.h>
#include <SDL_events.h>
#include <list>
#include <vector>
#include "entity.h"

class InputHandler {
protected:
    std::vector<InputComponent*>& componentList;
    std::list<Command*>& commandList;
    SwitchStateCommand quitCommand;
    SwitchStateCommand switchToMenu;
public:
    InputHandler(std::vector<InputComponent*>& componentList,
                 std::list<Command*>& commandList);
    virtual void handleEvents();
    void update(int dt);
};

#endif
