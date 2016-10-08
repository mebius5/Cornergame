#ifndef CORNERGAME_AI_COMPONENT_H
#define CORNERGAME_AI_COMPONENT_H

#include "entity.h"
#include "component.h"

class AiComponent : public Component {
public:
    AiComponent(Entity* entity);
    virtual void resetAi() = 0;
    virtual void updateLocation(int dt) = 0;
};

class EnemyAiComponent : public AiComponent {
private:
    int timeElapsed;      // time passed since a behavior was generated
    float speed;
public:
    EnemyAiComponent(Entity* entity);
    void resetAi();
    void updateLocation(int dt);
};

#endif
