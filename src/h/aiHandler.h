#ifndef CORNERGAME_AI_HANDLER_H
#define CORNERGAME_AI_HANDLER_H

#include "entity.h"
#include <list>
#include <map>

class AiHandler {
private:
    std::map<int, AiComponent*>& componentMap;
    std::list<Command*>& commandList;

public:
    AiHandler(std::map<int, AiComponent*>& componentMap,
              std::list<Command*>& commandList);
    void updateAi(int dt);
};

#endif
