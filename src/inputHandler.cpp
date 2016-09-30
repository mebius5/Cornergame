#include "inputHandler.h"

InputHandler::InputHandler(std::map<int, Entity*>& entMap,
                           std::list<Command*>& cmdList) :
        entityMap(entMap),
        commandList(cmdList),
        keystate(SDL_GetKeyboardState(NULL)) {
}

void InputHandler::handleEvent(SDL_Event& event) {
    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        if (it->second->input) {
            if (event.type == SDL_KEYUP)
                it->second->input->keyUp(event.key.keysym.sym);
            else if (event.type == SDL_KEYDOWN)
                it->second->input->keyDown(event.key.keysym.sym);
        }
    }
}

void InputHandler::update(int dt) {
    std::map<int, Entity*>::const_iterator it;
    for (it = this->entityMap.begin(); it != this->entityMap.end(); ++it) {
        if (it->second->input) {
            it->second->input->updateLocation(dt);
        }
    }
}
