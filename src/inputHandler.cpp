#include "inputHandler.h"

InputHandler::InputHandler(std::map<int, InputComponent*>& componentMap,
                           std::list<Command*>& commandList) :
    componentMap(componentMap),
    commandList(commandList),
    quitCommand(STATE_QUIT),
    switchToMenu(STATE_MENU) {
}

void InputHandler::handleEvents() {
    std::map<int, InputComponent*>::const_iterator it;
    SDL_Event event;
    Command* cmd = NULL;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            this->commandList.push_back(&this->quitCommand);
        else if (event.type != SDL_KEYUP && event.type != SDL_KEYDOWN)
            return;
        else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
            this->commandList.push_back(&this->quitCommand);
        else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)
            this->commandList.push_back(&this->switchToMenu);
        else {
            for (it = this->componentMap.begin(); it != this->componentMap.end(); ++it) {
                if (event.type == SDL_KEYUP)
                    cmd = it->second->keyUp(event.key.keysym.sym);
                else   // if type == SDL_KEYDOWN
                    cmd = it->second->keyDown(event.key.keysym.sym);
                if (cmd)
                    this->commandList.push_back(cmd);
            }
        }
    }
}

void InputHandler::update(int dt) {
    std::map<int, InputComponent*>::const_iterator it;
    for (it = this->componentMap.begin(); it != this->componentMap.end(); ++it)
        it->second->updateLocation(dt);
}
