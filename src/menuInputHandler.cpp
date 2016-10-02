#include "inputHandler.h"
#include <iostream>

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
    TextFadeInComponent* artComp = NULL;
    TextFadeInComponent* artComp2 = NULL;
    TextFadeInComponent* artComp3 = NULL;
    TextFadeInComponent* artComp4 = NULL;

    artComp = dynamic_cast<TextFadeInComponent*>(this->entityMap[this->selected + 2]->art);
    artComp->selectMenuItem();

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
                artComp = dynamic_cast<TextFadeInComponent*>(this->entityMap[this->selected + 2]->art);
                artComp->deselectMenuItem();
                this->selected = (this->selected-1)%5;
                if (this->selected < 0)
                    this->selected += 5;
                artComp2 = dynamic_cast<TextFadeInComponent*>(this->entityMap[this->selected + 2]->art);
                artComp2->selectMenuItem();
                break;
            case SDLK_DOWN:
                artComp3 = dynamic_cast<TextFadeInComponent*>(this->entityMap[this->selected + 2]->art);
                artComp3->deselectMenuItem();
                this->selected = (this->selected+1)%5;
                artComp4 = dynamic_cast<TextFadeInComponent*>(this->entityMap[this->selected + 2]->art);
                artComp4->selectMenuItem();
                break;
            case SDLK_SPACE:
                switch(selected+2){
                    case 2:
                        this->commandList.push_back(&this->switchToPlay);
                        return;
                    case 5:
                        this->commandList.push_back(&this->switchToHighscore);
                        return;
                    case 6:
                        this->commandList.push_back(&this->quitCommand);
                        return;;
                    default:
                        break;
                }
            }
        }
    }
}
