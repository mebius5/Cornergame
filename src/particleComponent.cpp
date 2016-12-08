#include "particleComponent.h"

ParticleComponent::ParticleComponent(Entity * entity, SpawnParticleCommand* spawnCommand):
    Component(entity),
    timeLeft(0),
    timeSinceSpawn(0),
    spawnInterval(20),
    spawnCommand(spawnCommand) {
}

ParticleComponent::~ParticleComponent() {
    this->entity = NULL;
    if (this->spawnCommand){
        delete this->spawnCommand;
        this->spawnCommand = NULL;
    }
}

void ParticleComponent::startSpawning(int time) {
    this->timeLeft = time;
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
        this->timeSinceSpawn -= this->spawnInterval;
        this->spawnCommand->x = this->entity->x;
        this->spawnCommand->y = this->entity->y;
        Component::commandList->push_back(this->spawnCommand);
    }
}
