#ifndef CORNERGAME_INPUT_HANDLER_H
#define CORNERGAME_INPUT_HANDLER_H

#include <SDL_keycode.h>
#include <map>
#include <list>
#include "entity.h"

class InputHandler {
private:
    std::map<int, Entity*>& entityMap;
    std::list<Command*>& commandList;
public:
    InputHandler(std::map<int, Entity*>& entMap, std::list<Command*>& cmdList);
    void handleKeyDown(SDL_Keycode event);
    //void pollKeys();
};

#endif //CORNERGAME_INPUT_HANDLER_H
