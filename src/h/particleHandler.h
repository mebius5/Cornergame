#ifndef CORNERGAME_PARTICLE_HANDLER_H
#define CORNERGAME_PARTICLE_HANDLER_H

#include "particleComponent.h"

class ParticleHandler {
private:
    std::vector<ParticleComponent*>& componentList;
public:
    ParticleHandler(std::vector<ParticleComponent*>& componentList);
    void update(int dt);
};

#endif
