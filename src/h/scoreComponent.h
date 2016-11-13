#ifndef CORNERGAME_SCORE_COMPONENT_H
#define CORNERGAME_SCORE_COMPONENT_H

#include "entity.h"
#include "component.h"

class ScoreComponent : public Component {
public:
    int wins;
    ScoreComponent(Entity* entity);
    ~ScoreComponent();
};

#endif
