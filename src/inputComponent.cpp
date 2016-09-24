#include "inputComponent.h"

InputComponent::InputComponent() {
    this->onLeft = NULL;
    this->onRight = NULL;
    this->onUp = NULL;
    this->onDown = NULL;
}

InputComponent::~InputComponent() {
    if (this->onLeft)
        delete this->onLeft;
    if (this->onRight)
        delete this->onRight;
    if (this->onUp)
        delete this->onUp;
    if (this->onDown)
        delete this->onDown;
}
