#include "inputHandler.h"

InputHandler::InputHandler(std::map<int, Entity*>& entMap,
                           std::list<Command*>& cmdList) :
        entityMap(entMap),
        commandList(cmdList),
        keystate(SDL_GetKeyboardState(NULL)) {
}

void InputHandler::pollKeys() {
    if (this->keystate[SDL_SCANCODE_LEFT])
        this->handleKeyDown(SDLK_LEFT);
    if (this->keystate[SDL_SCANCODE_RIGHT])
        this->handleKeyDown(SDLK_RIGHT);
    if (this->keystate[SDL_SCANCODE_UP])
        this->handleKeyDown(SDLK_UP);
    if (this->keystate[SDL_SCANCODE_DOWN])
        this->handleKeyDown(SDLK_DOWN);
}

void InputHandler::handleKeyDown(SDL_Keycode keycode) {
    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        if (it->second->input){
            Command* c = it->second->input->getKeyDownCmd(keycode);
            if (c)
                this->commandList.push_back(c);
        }
    }
}
