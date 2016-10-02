#include "inputComponent.h"

StartScreenInputComponent::StartScreenInputComponent(Entity *entity):
    InputComponent(entity){
}

StartScreenInputComponent::~StartScreenInputComponent() {
    this->entity = NULL;
}

void StartScreenInputComponent::keyUp(SDL_Keycode keycode) {

}

void StartScreenInputComponent::keyDown(SDL_Keycode keycode) {

}

void StartScreenInputComponent::updateLocation(int dt) {

}
