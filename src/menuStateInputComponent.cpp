#include "inputComponent.h"

MenuStateInputComponent::MenuStateInputComponent(Entity *entity):
        InputComponent(entity){
}

MenuStateInputComponent::~MenuStateInputComponent() {
    this->entity = NULL;
}

void MenuStateInputComponent::keyUp(SDL_Keycode keycode) {

}

void MenuStateInputComponent::keyDown(SDL_Keycode keycode) {

}

void MenuStateInputComponent::updateLocation(int dt) {

}