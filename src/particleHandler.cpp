#include "particleHandler.h"
#include <iostream>

ParticleHandler::ParticleHandler(std::vector<ParticleComponent*>& componentList) :
    componentList(componentList) {
}

void ParticleHandler::update(int dt) {
    std::vector<ParticleComponent*>::iterator it;
    for (it = this->componentList.begin(); it != this->componentList.end(); ) {
        if (!(*it)->isValid()) {        // remove invalid components
            *it = this->componentList.back();
            this->componentList.pop_back();
            continue;
        }
        // handle particles
        ParticleComponent * partComp = *it;
        partComp->update(dt);
        ++it;
    }
}
