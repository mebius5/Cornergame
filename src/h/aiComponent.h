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
    std::vector<Entity*>* heroEntities;
public:
    EnemyAiComponent(Entity* entity, std::vector<Entity*>* heroEntities);
    void resetAi();
    void updateLocation(int dt);
    void update(Entity *hero);
};

#endif
