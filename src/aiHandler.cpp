#include "aiHandler.h"

AiHandler::AiHandler(std::map<int, Entity*>& ent, std::list<Command*>& cmd) :
    entityMap(ent),
    commandList(cmd) {
}

void AiHandler::updateAi(int dt) {
    std::map<int, Entity*>::const_iterator it;
    for (it = this->entityMap.begin(); it != this->entityMap.end(); ++it) {
        if (it->second->ai) {
            it->second->ai->updateLocation(dt);
        }
    }
}
