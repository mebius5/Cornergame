#ifndef CORNERGAME_PARTICLE_COMPONENT_H
#define CORNERGAME_PARTICLE_COMPONENT_H

#include "entity.h"
#include "component.h"

class ParticleComponent : public Component {
private:
    int timeLeft;
    int timeSinceSpawn;
    int spawnInterval;
    SpawnParticleCommand* spawnCommand;
public:
    ParticleComponent(Entity* entity, SpawnParticleCommand* spawnCommand);
    ~ParticleComponent();
    void startSpawning(int upper, int lower);
    void update(int dt);
};

#endif
