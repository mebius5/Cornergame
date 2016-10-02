#include "inputComponent.h"

StartStateInputComponent::StartStateInputComponent(Entity *entity):
    InputComponent(entity){
}

StartStateInputComponent::~StartStateInputComponent() {
    this->entity = NULL;
}

void StartStateInputComponent::keyUp(SDL_Keycode keycode) {

}

void StartStateInputComponent::keyDown(SDL_Keycode keycode) {

}

void StartStateInputComponent::updateLocation(int dt) {

}