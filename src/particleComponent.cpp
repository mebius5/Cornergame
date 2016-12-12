#include "particleComponent.h"
#include <stdlib.h>
#include <stdio.h>

ParticleComponent::ParticleComponent(Entity * entity, SpawnParticleCommand* spawnCommand):
    Component(entity),
    timeLeft(0),
    timeSinceSpawn(0),
    spawnInterval(50),
    indefSpawn(false),
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

void ParticleComponent::slowSpawn() {
    this->spawnInterval = 150;
}

void ParticleComponent::fastSpawn() {
    this->spawnInterval = 50;
}

void ParticleComponent::startSpawning(int upper, int lower) {
    this->timeLeft = lower + rand() % (upper - lower);
}

void ParticleComponent::setIndefSpawn(bool spawn) {
    this->indefSpawn = spawn;
}

void ParticleComponent::update(int dt) {
    // see if out of time
    this->timeLeft -= dt;
    if (this->timeLeft <= 0) {
        this->timeLeft = 0;
        if (!this->indefSpawn) {
            return;
        }
    }

    // else spawn if enough time passed
    this->timeSinceSpawn += dt;
    if (this->timeSinceSpawn >= this->spawnInterval) {
        int num_spawns = this->timeSinceSpawn / this->spawnInterval;
        for (int i = 0; i < num_spawns; i++) {
            this->timeSinceSpawn -= this->spawnInterval;
            this->spawnCommand->x = this->entity->x;
            this->spawnCommand->y = this->entity->y;
            Component::commandList->push_back(this->spawnCommand);
        }
    }
}
