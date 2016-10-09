#ifndef CORNERGAME_AI_HANDLER_H
#define CORNERGAME_AI_HANDLER_H

#include <vector>
#include "entity.h"

class AiHandler {
private:
    std::vector<AiComponent*>& componentList;
    std::vector<Entity*> & heroEntitiesList;
public:
    AiHandler(std::vector<AiComponent*>& componentList, std::vector<Entity *> & heroEntityList);
    void updateAi(int dt);
};

#endif
