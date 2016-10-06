#include "aiHandler.h"

AiHandler::AiHandler(std::map<int, AiComponent*>& componentMap,
                     std::list<Command*>& commandList) :
    componentMap(componentMap),
    commandList(commandList) {
}

void AiHandler::updateAi(int dt) {
    std::map<int, AiComponent*>::const_iterator it;
    for (it = this->componentMap.begin(); it != this->componentMap.end(); ++it){
        if (it->second) {
            it->second->updateLocation(dt);
        }
    }
}
