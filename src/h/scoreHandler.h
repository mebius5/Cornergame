#ifndef CORNERGAME_SCORE_HANDLER_H
#define CORNERGAME_SCORE_HANDLER_H

#include "scoreComponent.h"

class ScoreHandler {
private:
    std::vector<ScoreComponent*>& componentList;
public:
    ScoreHandler(std::vector<ScoreComponent*>& componentList);
    void handleScore(int dt);
};

#endif
