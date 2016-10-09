#ifndef CORNERGAME_SCORE_COMPONENT_H
#define CORNERGAME_SCORE_COMPONENT_H

#include "entity.h"
#include "component.h"

class ScoreComponent : public Component {
private:
    float score;
    float multiplier;

public:
    ScoreComponent(Entity* entity);
    ~ScoreComponent();
    void addScore(float scoreIncrease);
    int getScore();
    void resetScore();
    void setMultiplier(float multiplier);
};

#endif
