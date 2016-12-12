#ifndef CORNERGAME_PARTICLE_COMPONENT_H
#define CORNERGAME_PARTICLE_COMPONENT_H

#include "entity.h"
#include "component.h"

class ParticleComponent : public Component {
private:
    int timeLeft;
    int timeSinceSpawn;
    int spawnInterval;
    bool indefSpawn;
    SpawnParticleCommand* spawnCommand;
public:
    ParticleComponent(Entity* entity, SpawnParticleCommand* spawnCommand);
    ~ParticleComponent();
    void slowSpawn();
    void fastSpawn();
    void startSpawning(int upper, int lower);
    void setIndefSpawn(bool spawn);
    void update(int dt);
};

#endif
