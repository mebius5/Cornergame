#include "powerUpComponent.h"

PowerUpComponent::PowerUpComponent(Entity * entity):
        Component(entity),
        timeElapsed(0),
        infiniteJumpActivated(false)
{
}

void PowerUpComponent::update(int dt) {
    this->timeElapsed+=dt;

    if(timeElapsed>=5000){ //5 seconds limit for all powerups

        if(this->infiniteJumpActivated){
            deactivateInfiniteJumpsPowerUp();
        }

    }
}

void PowerUpComponent::activateInfiniteJumpsPowerUp() {
    if(!entity->physics->isInfiniteJumpOn()){
        entity->physics->toggleInfiniteJumps();
        this->infiniteJumpActivated=true;
    }
}

void PowerUpComponent::deactivateInfiniteJumpsPowerUp() {
    if(entity->physics->isInfiniteJumpOn()){
        entity->physics->toggleInfiniteJumps();
        this->infiniteJumpActivated=false;
    }
}