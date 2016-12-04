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

    this->entity->actionState = ACTION_THROW;
    this->spawnCommand->dir = this->entity->dir;
    if (this->spawnCommand->dir == 1) {
        this->spawnCommand->x = entity->x + this->entity->width + 16;
    } else {
        this->spawnCommand->x = entity->x - 32;
    }
    this->spawnCommand->y = entity->y+20;
    this->spawnCommand->ownerID = this->entity->getId();
    this->spawnCommand->charge = charge;
    Component::commandList->push_back(this->spawnCommand);

    if (!this->isUnlimited) {
        this->ammo -= 1;
    }
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
