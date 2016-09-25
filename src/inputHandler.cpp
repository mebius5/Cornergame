#include "inputHandler.h"

InputHandler::InputHandler(std::map<int, Entity*>& entityMap,
                           std::list<Command*>& cmdList):
        entityMap(entityMap), commandList(cmdList) {
}

void InputHandler::handleKeyDown(SDL_Event event) {
    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        if (it->second->input){
            Command* c = it->second->input->getKeyDownCmd(event.key.keysym.sym);
            if (c)
                this->commandList.push_back(c);
        }
    }
}
