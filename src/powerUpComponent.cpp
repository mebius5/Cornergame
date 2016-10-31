#include "powerUpComponent.h"

PowerUpComponent::PowerUpComponent(Entity * entity):
        Component(entity),
        timeElapsed(0),
        infJumpActivated(false),
        infHealthActivated(false)
{
}

void PowerUpComponent::update(int dt) {

    if(this->infJumpActivated || this->infHealthActivated){
        this->timeElapsed+=dt;
    }

    if(timeElapsed>=3500){ //3.5 seconds limit for all powerups

        if(this->infJumpActivated){
            //std::cout<<"The time has expired."<<std::endl;
            this->timeElapsed=0;
            deactivateInfJumpPwrUp();
        }

        if(this->infHealthActivated){
            this->timeElapsed=0;
            deactivateInfHealthPwrUp();
        }

    }
}

void PowerUpComponent::activateInfJumpPwrUp() {
    if(!entity->physics->isInfiniteJumpOn()){
        entity->physics->toggleInfiniteJumps();
        this->infJumpActivated=true;
        //std::cout<<"The jump is activated."<<std::endl;
    }
}

void PowerUpComponent::deactivateInfJumpPwrUp() {
    if(entity->physics->isInfiniteJumpOn()){
        entity->physics->toggleInfiniteJumps();
        this->infJumpActivated=false;
    }
}

void PowerUpComponent::activateInfHealthPwrUp() {
    if(!entity->health->isIsInvincible()){
        entity->health->toggleInvincibility();
        this->infHealthActivated=true;
    }
}

void PowerUpComponent::deactivateInfHealthPwrUp() {
    if(entity->health->isIsInvincible()){
        entity->health->toggleInvincibility();
        this->infHealthActivated=false;
    }
}
