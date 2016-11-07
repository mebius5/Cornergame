#include "powerUpComponent.h"

PowerUpComponent::PowerUpComponent(Entity * entity):
        Component(entity),
        pwrUpTimerArraySize(4), //Need to initialize the array as well, also change h file
        pwrUPTimerArray{-999,-999,-999,-999} //Initial and default values
{
}

void PowerUpComponent::update(int dt) {

    for(int i = 0 ; i<pwrUpTimerArraySize ;i++){
        if(pwrUPTimerArray[i]>0){
            pwrUPTimerArray[i]-=dt;
        }

        if(pwrUPTimerArray[i]!=-999 && pwrUPTimerArray[i]<=0){
            switch (i){
                case (int)TEX_PWRUP_INFJUMP:
                    deactivateInfJumpPwrUp();
                    break;
                case (int)TEX_PWRUP_INFHEALTH:
                    deactivateInfHealthPwrUp();
                    break;
                case (int)TEX_PWRUP_AMMO:
                    break; //One time thing for ammo, so no deactivation
                case (int)TEX_PWRUP_BEER:
                    deactivateBeerPwrUp();
                    break;
                default:
                    break;
            }
        }
    }

}

void PowerUpComponent::activatePowerUp(TextureEnum pwrUpType) {
    switch (pwrUpType){
        case TEX_PWRUP_INFJUMP:{
            activateInfJumpPwrUp();
            break;
        }
        case TEX_PWRUP_INFHEALTH:{
            activateInfHealthPwrUp();
            break;
        }
        case TEX_PWRUP_AMMO:{
            activateIncreaseAmmo();
            break;
        }
        case TEX_PWRUP_BEER:{
            activateBeerPwrUp();
            break;
        }
        default:
            break;
    }
}

void PowerUpComponent::activateInfJumpPwrUp() {
    int timeLimit = 3500;
    if(!entity->physics->isInfiniteJumpOn()){
        entity->physics->toggleInfiniteJumps();
        this->pwrUPTimerArray[(int)TEX_PWRUP_INFJUMP]=timeLimit;
    }else{
        //If activated from power up and not from cheat
        if(this->pwrUPTimerArray[(int)TEX_PWRUP_INFJUMP]!=-999){
            this->pwrUPTimerArray[(int)TEX_PWRUP_INFJUMP]=timeLimit;
        }
    }
}

void PowerUpComponent::deactivateInfJumpPwrUp() {
    if(entity->physics->isInfiniteJumpOn()){
        entity->physics->toggleInfiniteJumps();
        this->pwrUPTimerArray[(int)TEX_PWRUP_INFJUMP]=-999;
    }
}

void PowerUpComponent::activateInfHealthPwrUp() {
    int timeLimit = 5000;
    if(!entity->health->isIsInvincible()){
        entity->health->toggleInvincibility();
        this->pwrUPTimerArray[(int)TEX_PWRUP_INFHEALTH]=timeLimit;
    }else{ //If is already turned on
        //If activated from power up and not from cheat
        if(this->pwrUPTimerArray[(int)TEX_PWRUP_INFHEALTH]!=-999){

            this->pwrUPTimerArray[(int)TEX_PWRUP_INFHEALTH]=timeLimit;
        }
    }
}

void PowerUpComponent::deactivateInfHealthPwrUp() {
    if(entity->health->isIsInvincible()){
        entity->health->toggleInvincibility();
        this->pwrUPTimerArray[(int)TEX_PWRUP_INFHEALTH]=-999;
    }
}

void PowerUpComponent::activateIncreaseAmmo() {
    entity->ammo->addAmmo(5);
}

void PowerUpComponent::activateBeerPwrUp() {
    int timeLimit = 5000;

    if(HeroInputComponent * hic = dynamic_cast<HeroInputComponent *>(entity->input)){
        hic->invertControl();
        this->pwrUPTimerArray[(int)TEX_PWRUP_BEER]=timeLimit;
    }else{ //If is already turned on
        //If activated from power up and not from cheat
        if(this->pwrUPTimerArray[(int)TEX_PWRUP_BEER]!=-999){
            this->pwrUPTimerArray[(int)TEX_PWRUP_BEER]=timeLimit;
        }
    }
}

void PowerUpComponent::deactivateBeerPwrUp() {
    if(HeroInputComponent * hic = dynamic_cast<HeroInputComponent *>(entity->input)){
        hic->invertControl();
        this->pwrUPTimerArray[(int)TEX_PWRUP_BEER]=-999;
    }
}