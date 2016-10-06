#ifndef CORNERGAME_SCORE_COMPONENT_H
#define CORNERGAME_SCORE_COMPONENT_H

#include "entity.h"
#include "component.h"

class ScoreComponent : public Component {
    private:
        int score;
        float multiplier;

    public:
        ScoreComponent(Entity* entity);
        ~ScoreComponent();
        void addScore(int scoreIncrease);
        int getScore();
        void resetScore();
        void setMultiplier(float multiplier);
};

#endif
