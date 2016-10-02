#include "inputComponent.h"

MenuOptionInputComponent::MenuOptionInputComponent(Entity *entity, int index,
                                                   int numOptions,
                                                   Command* selectCommand,
                                                   Command* deselectCommand,
                                                   Command* nextStateCmd) :
        InputComponent(entity),
        index(index),
        numOptions(numOptions),
        currIndex(0),
        selected(index == 0),
        selectCommand(selectCommand),
        deselectCommand(deselectCommand),
        nextStateCommand(nextStateCmd) {
            if (index == currIndex) {
                TextFadeInComponent* artComp = dynamic_cast<TextFadeInComponent*>(this->entity->art);
                artComp->selectMenuItem();
            }
}

MenuOptionInputComponent::~MenuOptionInputComponent() {
    if (this->selectCommand)
        delete this->selectCommand;
    if (this->deselectCommand)
        delete this->deselectCommand;
    if (this->nextStateCommand)
        delete this->nextStateCommand;
}

Command* MenuOptionInputComponent::keyUp(SDL_Keycode keycode) {
    return NULL;
}

Command* MenuOptionInputComponent::keyDown(SDL_Keycode keycode) {
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
        if (this->selected && this->nextStateCommand)
            return this->nextStateCommand;
        else
            return NULL;
    default:
        return NULL;
    }

    // Check if we need to select ourself or deselect ourself
    TextFadeInComponent* artComp = dynamic_cast<TextFadeInComponent*>(this->entity->art);
    if (this->selected) {
        this->selected = false;
        artComp->deselectMenuItem();
    } else if (this->currIndex == this->index) {
        this->selected = true;
        artComp->selectMenuItem();
    }
    return NULL;
}

void MenuOptionInputComponent::updateLocation(int dt) {

}
