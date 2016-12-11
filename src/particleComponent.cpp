#include "particleComponent.h"
#include <stdlib.h>

ParticleComponent::ParticleComponent(Entity * entity, SpawnParticleCommand* spawnCommand):
    Component(entity),
    timeLeft(0),
    timeSinceSpawn(0),
    spawnInterval(50),
    spawnCommand(spawnCommand) {
        srand(time(NULL));
}

ParticleComponent::~ParticleComponent() {
    this->entity = NULL;
    if (this->spawnCommand){
        delete this->spawnCommand;
        this->spawnCommand = NULL;
    }
}

void ParticleComponent::startSpawning(int upper, int lower) {
    this->timeLeft = lower + rand() % (upper - lower);
}

void ParticleComponent::update(int dt) {
    // see if out of time
    this->timeLeft -= dt;
    if (this->timeLeft <= 0) {
        this->timeLeft = 0;
        return;
    }

    // else spawn if enough time passed
    this->timeSinceSpawn += dt;
    if (this->timeSinceSpawn >= this->spawnInterval) {
        for (int i = 0; i < this->timeSinceSpawn / this->spawnInterval; i++) {
            this->timeSinceSpawn -= this->spawnInterval;
            this->spawnCommand->x = this->entity->x;
            this->spawnCommand->y = this->entity->y;
            Component::commandList->push_back(this->spawnCommand);
        }
    }
}
