#ifndef CORNERGAME_AI_HANDLER_H
#define CORNERGAME_AI_HANDLER_H

#include <list>
#include <map>
#include "entity.h"

class AiHandler {
private:
    std::map<int, AiComponent*>& componentMap;
public:
    AiHandler(std::map<int, AiComponent*>& componentMap);
    void updateAi(int dt);
};

#endif
