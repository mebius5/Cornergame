#include "inputComponent.h"

// note: this file is not currently in the Makefile.
// TODO: cheat codes?

StartScreenInputComponent::StartScreenInputComponent(Entity* entity):
    InputComponent(entity){
}

StartScreenInputComponent::~StartScreenInputComponent() {
    this->entity = NULL;
}

void StartScreenInputComponent::keyUp(SDL_Keycode /*keycode*/) {

}

void StartScreenInputComponent::keyDown(SDL_Keycode /*keycode*/) {

}
