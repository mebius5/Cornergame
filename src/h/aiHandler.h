#ifndef CORNERGAME_AI_HANDLER_H
#define CORNERGAME_AI_HANDLER_H

#include "entity.h"
#include <list>
#include <map>

class AiHandler {
private:
    std::map<int, Entity*>& entityMap;
    std::list<Command*>& commandList;

public:
    AiHandler(std::map<int, Entity*>& entityMap, std::list<Command*>& cmdList);
    void updateAi(int dt);
};

#endif
