#include "inputComponent.h"

// NOTE: this file is not currently in the Makefile.
// TODO: cheat codes?

StartScreenInputComponent::StartScreenInputComponent(Entity* entity):
    InputComponent(entity){
}

StartScreenInputComponent::~StartScreenInputComponent() {
    this->entity = NULL;
}

void StartScreenInputComponent::updateTime(int /*dt*/) {
}

void StartScreenInputComponent::keyUp(SDL_Keycode /*keycode*/) {

}

void StartScreenInputComponent::keyDown(SDL_Keycode /*keycode*/) {

}
