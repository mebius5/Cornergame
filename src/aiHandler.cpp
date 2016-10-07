#include "aiHandler.h"

AiHandler::AiHandler(std::vector<AiComponent*>& componentList) :
    componentList(componentList) {
}

void AiHandler::updateAi(int dt) {
    std::vector<AiComponent*>::iterator it;
    for (it = this->componentList.begin(); it != this->componentList.end(); ) {
        if (!(*it)->isValid()) {        // remove invalid components
            *it = this->componentList.back();
            this->componentList.pop_back();
        } else {
            (*it)->updateLocation(dt);
            ++it;
        }
    }
}
