#include "inputComponent.h"

InputComponent::InputComponent() {

}

InputComponent::~InputComponent() {

}

void InputComponent::insertKeyDown(SDL_Keycode keycode, Command * command){
    this->onKeyDownMap[keycode]=command;
};