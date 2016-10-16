#ifndef CORNERGAME_AI_HANDLER_H
#define CORNERGAME_AI_HANDLER_H

#include <vector>
#include "entity.h"

class AiHandler {
private:
    std::vector<AiComponent*>& componentList;
public:
    AiHandler(std::vector<AiComponent*>& componentList);
    void updateAi(int dt);
};

#endif
