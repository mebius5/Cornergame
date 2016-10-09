
#ifndef CORNERGAME_SCOREHANDLER_H
#define CORNERGAME_SCOREHANDLER_H

#include "scoreComponent.h"

class ScoreHandler {
private:
private:
    std::vector<ScoreComponent*>& componentList;
public:
    ScoreHandler(std::vector<ScoreComponent*>& componentList);
    void handleScore(int dt);
};

#endif //CORNERGAME_SCOREHANDLER_H
