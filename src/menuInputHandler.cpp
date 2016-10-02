#include "inputHandler.h"

MenuInputHandler::MenuInputHandler(std::map<int, Entity*>& entityMap,
                                   std::list<Command*>& commandList) :
        InputHandler(entMap, cmdList),
        switchToPlay(3),
        switchToHighscore(5),
        selected(0) {
}

void MenuInputHandler::handleEvents() {
    std::map<int, Entity*>::const_iterator it;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            this->commandList.push_back(&this->quitCommand);
            return;
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                this->commandList.push_back(&this->quitCommand);
                return;

            case SDLK_UP:
                this->entityMap[this->selected + 1].deselectMenuItem();
                this->selected = (this->selected-1)%3
                this->entityMap[this->selected + 1].selectMenuItem();
                break;
            case SDLK_DOWN:
                this->entityMap[this->selected + 1].deselectMenuItem();
                this->selected = (this->selected+1)%3
                this->entityMap[this->selected + 1].selectMenuItem();
                break;
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
