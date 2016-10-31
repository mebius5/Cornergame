#include "ammoComponent.h"

AmmoComponent::AmmoComponent(Entity * entity, int maxAmmo):
    Component(entity),
    ammo(maxAmmo),
    maxAmmo(maxAmmo),
    isUnlimited(false) {
}

AmmoComponent::~AmmoComponent() {
    this->entity = NULL;
}

int AmmoComponent::getAmmo() {
    return this->ammo;
}

int AmmoComponent::getMaxAmmo() {
    return this->maxAmmo;
}

void AmmoComponent::toggleUnlimited() {
    if(this->isUnlimited){
        this->isUnlimited=false;
    } else{
        this->isUnlimited=true;
    }
}

void AmmoComponent::spendAmmo() {
    if(!this->isUnlimited){
        this->ammo -= 1;
        if (this->ammo < 0) {
            this->ammo = 0;
        }
    }
}

bool AmmoComponent::hasAmmo() {
    return (this->ammo > 0 || this->isUnlimited);
}

void AmmoComponent::addAmmo(int amount) {
    this->ammo += amount;
    if (this->ammo > this->maxAmmo) {
        this->ammo = this->maxAmmo;
    }
}
