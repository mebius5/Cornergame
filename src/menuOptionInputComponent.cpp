#include "inputComponent.h"

MenuOptionInputComponent::MenuOptionInputComponent(Entity *entity, int index,
                            int numOptions, Command* nextStateCmd) :
    InputComponent(entity),
    index(index),
    numOptions(numOptions),
    currIndex(0),
    selected(index == 0),
    nextStateCommand(nextStateCmd) {

    TextFadeInComponent* art = static_cast<TextFadeInComponent*>(entity->art);
    if (index == currIndex)
        art->selectMenuItem();
}

MenuOptionInputComponent::~MenuOptionInputComponent() {
    if (this->nextStateCommand)
        delete this->nextStateCommand;
}

void MenuOptionInputComponent::keyUp(SDL_Keycode /*keycode*/) {
}

void MenuOptionInputComponent::keyDown(SDL_Keycode keycode) {
    // Check if up arrow or down arrow was pressed
    switch (keycode) {
    case SDLK_UP:
        this->currIndex--;
        if (this->currIndex < 0)
            this->currIndex = this->numOptions - 1;
        break;
    case SDLK_DOWN:
        this->currIndex++;
        if (this->currIndex == numOptions)
            this->currIndex = 0;
        break;
    case SDLK_SPACE:
        if (this->nextStateCommand && this->selected)
            Component::commandList->push_back(this->nextStateCommand);
        return;
    default:
        return;
    }

    // Check if we need to select ourself or deselect ourself
    TextFadeInComponent* art = static_cast<TextFadeInComponent*>(this->entity->art);
    if (this->selected) {
        this->selected = false;
        art->deselectMenuItem();
    } else if (this->currIndex == this->index) {
        this->selected = true;
        art->selectMenuItem();
    }
}
