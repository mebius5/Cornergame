#include "inputHandler.h"

InputHandler::InputHandler(std::map<int, Entity*>& entityMap,
                           std::list<Command*>& commandList) :
        entityMap(entityMap),
        commandList(commandList),
        quitCommand(1), // return QUIT
        switchToMenu(4) {    // return MENU
}

void InputHandler::handleEvents() {
    std::map<int, Entity*>::const_iterator it;
    SDL_Event event;
    Command* cmd;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYUP
                    && event.key.keysym.sym == SDLK_ESCAPE)) {
            this->commandList.push_back(&this->quitCommand);
            return;
        }

        if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q) {
            this->commandList.push_back(&this->switchToMenu);
            return;
        }

        for (it = entityMap.begin(); it != entityMap.end(); ++it) {
            if (it->second->input) {
                if (event.type == SDL_KEYUP)
                    cmd = it->second->input->keyUp(event.key.keysym.sym);
                else if (event.type == SDL_KEYDOWN)
                    cmd = it->second->input->keyDown(event.key.keysym.sym);
                if (cmd)
                    this->commandList.push_back(cmd);
            }
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
