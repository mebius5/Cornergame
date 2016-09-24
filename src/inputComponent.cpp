#include "inputComponent.h"

InputComponent::InputComponent() {

}

InputComponent::~InputComponent() {
    std::map<SDL_Keycode , Command *>::const_iterator it;
    for(it=onKeyDownMap.begin();it!=onKeyDownMap.end();++it){
        if(it->second){
            delete it->second;
        }
    }
}

void InputComponent::insertKeyDown(SDL_Keycode keycode, Command * command){
    this->onKeyDownMap[keycode]=command;
};