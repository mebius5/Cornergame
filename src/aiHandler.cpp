#include "aiHandler.h"

AiHandler::AiHandler(std::map<int, Entity*>& entityMap,
                     std::list<Command*>& cmdList) :
        entityMap(entityMap), commandList(cmdList) {
}

void AiHandler::handleAi(float time) {
    std::map<int, Entity*>::const_iterator it;
    for (it = this->entityMap.begin(); it != this->entityMap.end(); ++it) {
        if (it->second->ai) {
            this->commandList.push_back(it->second->ai->generateBehavior(time));
        }
    }
}
