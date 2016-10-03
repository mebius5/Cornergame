#ifndef CORNERGAME_AI_COMPONENT_H
#define CORNERGAME_AI_COMPONENT_H

#include "entity.h"
#include "component.h"

class Entity;

class AiComponent : public Component {
private:
    int timeElapsed;      // time passed since a behavior was generated
    float speed;

public:
    AiComponent(Entity* entity);
    void updateLocation(int dt);
    void resetAi();
};

#endif
