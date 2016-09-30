#ifndef CORNERGAME_INPUT_HANDLER_H
#define CORNERGAME_INPUT_HANDLER_H

#include <SDL.h>
#include <SDL_events.h>
#include <map>
#include <list>
#include "entity.h"

class InputHandler {
private:
    std::map<int, Entity*>& entityMap;
    std::list<Command*>& commandList;
    const Uint8* keystate;   // ptr to SDL's internal scancode keyboard states
public:
    InputHandler(std::map<int, Entity*>& entMap, std::list<Command*>& cmdList);
    void handleEvent(SDL_Event& event);
    void update(int dt);
};

#endif
