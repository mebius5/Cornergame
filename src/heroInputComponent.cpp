#include "inputComponent.h"

HeroInputComponent::HeroInputComponent(Entity* entity, bool wasd, SpawnProjCommand* spawnCommand) :
    InputComponent(entity),
    runCommand(new PlaySoundCommand(SFX_RUNNING)),
    stopCommand(new StopSoundCommand(SFX_RUNNING)),
    upKey(wasd ? SDLK_w : SDLK_UP),
    downKey(wasd ? SDLK_s : SDLK_DOWN),
    leftKey(wasd ? SDLK_a : SDLK_LEFT),
    rightKey(wasd ? SDLK_d : SDLK_RIGHT),
    shootKey(wasd ? SDLK_v : SDLK_m),
    jumpPressed(false),
    spawnCommand(spawnCommand),
    holdTime(-1.0f),
    maxHold(500.0f) {
}

HeroInputComponent::~HeroInputComponent() {
    this->entity = NULL;
    if (spawnCommand) {
        delete spawnCommand;
    }
    if (runCommand) {
        delete runCommand;
    }
    if (stopCommand) {
        delete stopCommand;
    }
}

void HeroInputComponent::updateTime(int dt) {
    // update the hold time
    if (this->holdTime >= 0) {
        this->holdTime += dt;
        if (this->holdTime > this->maxHold) {
            this->holdTime = this->maxHold;
        }
    }
}

void HeroInputComponent::keyDown(SDL_Keycode keycode) {
    if (keycode == this->upKey) {
        if (!this->jumpPressed) {
            this->entity->physics->jump();
            this->jumpPressed = true;
        }
        this->entity->physics->accelerateY(-1);
    //} else if (keycode == this->downKey) {
    //    this->entity->physics->accelerateY(1);
    } else if (keycode == this->leftKey) {
        this->entity->physics->accelerateX(-1);
        this->entity->dir = -1;
        if (this->runCommand && dynamic_cast<HeroCollisionComponent*>(this->entity->collision)->onGround)
            Component::commandList->push_back(this->runCommand);
    } else if (keycode == this->rightKey) {
        this->entity->physics->accelerateX(1);
        this->entity->dir = 1;
        if (this->runCommand && dynamic_cast<HeroCollisionComponent*>(this->entity->collision)->onGround)
            Component::commandList->push_back(this->runCommand);
    } else if (keycode == this->shootKey) {
        // start to charge the shot
        if (this->holdTime < 0) {
            this->holdTime = 0.0f;
        }

    } else if (keycode == SDLK_k) {
        this->entity->health->toggleInvincibility();
        this->entity->physics->toggleInfiniteJumps();
    } else if (keycode == SDLK_l) {
        this->entity->health->die();
    }
}

void HeroInputComponent::keyUp(SDL_Keycode keycode) {
    if (keycode == this->upKey) {
        this->jumpPressed = false;
        this->entity->physics->clearAccelerationY();
    //} else if (keycode == this->downKey) {
    //    this->entity->physics->clearAccelerationY();
    } else if (keycode == this->leftKey || keycode == this->rightKey) {
        this->entity->physics->clearAccelerationX();
        if (this->stopCommand)
            Component::commandList->push_back(this->stopCommand);
    } else if (keycode == this->shootKey) {
        // don't allow a shot if not charged
        if (this->holdTime <= 0) {
            return;
        }

        // check if enough ammo to shoot
        if (!this->entity->ammo->hasAmmo()) {
            return;
        }
        this->entity->ammo->spendAmmo();

        this->entity->actionState = ACTION_THROW;
        this->spawnCommand->dir = this->entity->dir;
        if (this->spawnCommand->dir == 1) {
            this->spawnCommand->x = entity->x + this->entity->width + 16; // TODO remove magic numbers
        } else {
            this->spawnCommand->x = entity->x - 32;
        }
        this->spawnCommand->y = entity->y+20;
        this->spawnCommand->ownerID = entity->getId();
        this->spawnCommand->charge = this->holdTime / this->maxHold;
        Component::commandList->push_back(this->spawnCommand);

        // reset hold time
        this->holdTime = -1.0f;
    }
}

void HeroInputComponent::invertControl() {
    SDL_Keycode tempKey;
    tempKey = this->upKey;
    this->upKey = this->downKey;
    this->downKey = tempKey;

    tempKey = this->rightKey;
    this->rightKey = this->leftKey;
    this->leftKey = tempKey;
}
