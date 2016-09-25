#include "inputHandler.h"

InputHandler::InputHandler(std::map<int, Entity*>& entMap,
                           std::list<Command*>& cmdList):
        entityMap(entMap), commandList(cmdList) {
}

// void InputHandler::pollKeys() {
//     const Uint8* keystate = SDL_GetKeyboardState(NULL);
//     if (keystate[SDLK_LEFT])
//         this->handleKeyDown(SDLK_LEFT);
//     if (keystate[SDLK_RIGHT])
//         this->handleKeyDown(SDLK_RIGHT);
//     if (keystate[SDLK_UP])
//         this->handleKeyDown(SDLK_UP);
//     if (keystate[SDLK_DOWN])
//         this->handleKeyDown(SDLK_DOWN);
// }

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
