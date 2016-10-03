#include "inputComponent.h"

// note: this file is not currently in the Makefile.
// TODO: cheat codes?

StartScreenInputComponent::StartScreenInputComponent(Entity* entity):
    InputComponent(entity){
}

StartScreenInputComponent::~StartScreenInputComponent() {
    this->entity = NULL;
}

Command* StartScreenInputComponent::keyUp(SDL_Keycode /*keycode*/) {
    return NULL;
}

Command* StartScreenInputComponent::keyDown(SDL_Keycode /*keycode*/) {
    return NULL;
}

void StartScreenInputComponent::updateLocation(int /*dt*/) {

}
