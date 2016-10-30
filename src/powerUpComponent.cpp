#include "powerUpComponent.h"

PowerUpComponent::PowerUpComponent(Entity * entity):
        Component(entity),
        timeElapsed(0),
        infiniteJumpActivated(false)
{
}

void PowerUpComponent::update(int dt) {

    if(this->infiniteJumpActivated){
        this->timeElapsed+=dt;

    }

    if(timeElapsed>=3500){ //3.5 seconds limit for all powerups

        if(this->infiniteJumpActivated){
            std::cout<<"The time has expired."<<std::endl;
            this->timeElapsed=0;
            deactivateInfiniteJumpsPowerUp();
        }

    }
}

void PowerUpComponent::activateInfiniteJumpsPowerUp() {
    if(!entity->physics->isInfiniteJumpOn()){
        entity->physics->toggleInfiniteJumps();
        this->infiniteJumpActivated=true;
        std::cout<<"The jump is activated."<<std::endl;
    }
}

void PowerUpComponent::deactivateInfiniteJumpsPowerUp() {
    if(entity->physics->isInfiniteJumpOn()){
        entity->physics->toggleInfiniteJumps();
        this->infiniteJumpActivated=false;
    }
}