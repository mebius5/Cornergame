#include "aiHandler.h"

AiHandler::AiHandler(std::map<int, Entity*>& ent, std::list<Command*>& cmd) :
    entityMap(ent),
    commandList(cmd) {
}

void AiHandler::update(int dt) {
    std::map<int, Entity*>::const_iterator it;
    for (it = this->entityMap.begin(); it != this->entityMap.end(); ++it) {
        if (it->second->ai) {
            it->second->ai->updateLocation(dt);
        }
    }
}

void AiHandler::handleAiCommands() {
    std::list<Command*>::const_iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end(); ) {
        Command* c = *it;
        if (ResetAiCommand* resetCmd = dynamic_cast<ResetAiCommand*>(c)) {
            resetCmd->entity->ai->resetAi();
            it = this->commandList.erase(it);
        } else {
            ++it;
        }
    }
}
