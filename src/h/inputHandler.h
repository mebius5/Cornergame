#ifndef CORNERGAME_INPUT_HANDLER_H
#define CORNERGAME_INPUT_HANDLER_H

#include <SDL.h>
#include <SDL_events.h>
#include <map>
#include <list>
#include "entity.h"

class InputHandler {
protected:
    std::map<int, Entity*>& entityMap;
    std::list<Command*>& commandList;
    SwitchStateCommand quitCommand;
    SwitchStateCommand switchToMenu;
public:
    InputHandler(std::map<int, Entity*>& entMap, std::list<Command*>& cmdList);
    virtual void handleEvents();
    void update(int dt);
};

#endif
