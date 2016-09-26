#include "inputComponent.h"

InputComponent::InputComponent(float speed) :
        speed(speed) {
}

InputComponent::~InputComponent() {
    std::map<SDL_Keycode, Command*>::const_iterator it;
    for (it = this->onKeyDown.begin(); it != this->onKeyDown.end(); ++it) {
        delete it->second;
    }
}

void InputComponent::insertKeyDown(SDL_Keycode keycode, Command* command){
    this->onKeyDown[keycode] = command;
}

Command* InputComponent::getKeyDownCmd(SDL_Keycode keycode) {
    try {
        return this->onKeyDown.at(keycode);
    } catch (const std::out_of_range& oor) {
        return NULL;
    }
}
