#include "ammoComponent.h"

AmmoComponent::AmmoComponent(Entity * entity, int maxAmmo):
    Component(entity),
    ammo(maxAmmo),
    maxAmmo(maxAmmo),
    spawnCommand(new SpawnProjCommand(PROJ_HERO)),
    bombCommand(new SpawnProjCommand(PROJ_BOMB)),
    hasBomb(false),
    isUnlimited(false) {
}

AmmoComponent::~AmmoComponent() {
    this->entity = NULL;
    delete this->bombCommand;
    delete this->spawnCommand;
}

int AmmoComponent::getAmmo() {
    return this->ammo;
}

int AmmoComponent::getMaxAmmo() {
    return this->maxAmmo;
}

void AmmoComponent::toggleUnlimited() {
    this->isUnlimited= !this->isUnlimited;
}

void AmmoComponent::spendAmmo(float charge) {
    // check if enough ammo to shoot
    if (this->ammo <= 0 && !this->isUnlimited)
        return;

    SpawnProjCommand* command;
    if (this->hasBomb) {
        command = this->bombCommand;
        this->hasBomb = false;
    } else {
        command = this->spawnCommand;
        if (!this->isUnlimited) {
            this->ammo -= 1;
        }
    }

    this->entity->actionState = ACTION_THROW;
    command->dir = this->entity->dir;
    if (command->dir == 1) {
        command->x = entity->x + this->entity->width + 16;
    } else {
        command->x = entity->x - 32;
    }
    command->y = entity->y+20;
    command->ownerID = this->entity->getId();
    command->charge = charge;
    Component::commandList->push_back(command);
}

void AmmoComponent::addAmmo(int amount) {
    this->ammo += amount;
    if (this->ammo > this->maxAmmo) {
        this->ammo = this->maxAmmo;
    }
}

void AmmoComponent::addBomb() {
    this->hasBomb = true;
}
