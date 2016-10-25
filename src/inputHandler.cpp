#include "inputHandler.h"

InputHandler::InputHandler(std::vector<InputComponent*>& componentList,
                           std::vector<Command*>& commandList) :
    componentList(componentList),
    commandList(commandList),
    quitCommand(STATE_QUIT),
    switchToMenu(STATE_MENU),
    previewOff()
{
}

void InputHandler::handleEvents() {
    std::vector<InputComponent*>::iterator it;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            this->commandList.push_back(&this->quitCommand);
        else if (event.type != SDL_KEYUP && event.type != SDL_KEYDOWN)
            return;
        else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
            this->commandList.push_back(&this->quitCommand);
        else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)
            this->commandList.push_back(&this->switchToMenu);
        else if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_p)
            this->commandList.push_back(&this->previewOff);
        else {
            for (it = this->componentList.begin(); it != this->componentList.end(); ) {
                if (!(*it)->isValid()) {        // remove invalid components
                    *it = this->componentList.back();
                    this->componentList.pop_back();
                    continue;
                }

                if (event.type == SDL_KEYUP)
                    (*it)->keyUp(event.key.keysym.sym);
                else   // if type == SDL_KEYDOWN
                    (*it)->keyDown(event.key.keysym.sym);
                ++it;
            }
        }
    }
}
