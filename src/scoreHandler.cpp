#include "scoreHandler.h"

ScoreHandler::ScoreHandler(std::vector < ScoreComponent * > &componentList):
componentList(componentList)
{
}

void ScoreHandler::handleScore(int dt) {
    std::vector<ScoreComponent*>::iterator it;
        for (it = this->componentList.begin(); it != this->componentList.end(); ) {
            if (!(*it)->isValid()) {        // remove invalid components
                *it = this->componentList.back();
                this->componentList.pop_back();
                continue;
            }

            ScoreComponent* scoreComp = *it;
            scoreComp->addScore(((float)dt)/10);
            ++it;
        }
}