#include "inputHandler.h"

MenuInputHandler::MenuInputHandler(std::map<int, Entity*>& entityMap,
                                   std::list<Command*>& commandList) :
        InputHandler(entityMap, commandList),
        switchToPlay(3),
        switchToHighscore(5),
        selected(0) {
}

void MenuInputHandler::handleEvents() {
    std::map<int, Entity*>::const_iterator it;
    SDL_Event event;
    Command* cmd = NULL;

    //artComp = dynamic_cast<TextFadeInComponent*>(this->entityMap[this->selected + 2]->art);
    //artComp->selectMenuItem();

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            this->commandList.push_back(&this->quitCommand);
            return;
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                this->commandList.push_back(&this->quitCommand);
                return;
            default:
                for (it = entityMap.begin(); it != entityMap.end(); ++it) {
                    if (it->second->input)
                        cmd = it->second->input->keyDown(event.key.keysym.sym);
                    if (cmd)
                        this->commandList.push_back(cmd);
                }
                break;
            }
        }
    }
}
