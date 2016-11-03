#include "inputComponent.h"

HeroInputComponent::HeroInputComponent(Entity* entity, bool wasd, SpawnProjCommand* spawnCommand) :
    InputComponent(entity),
    upKey(wasd ? SDLK_w : SDLK_UP),
    downKey(wasd ? SDLK_s : SDLK_DOWN),
    leftKey(wasd ? SDLK_a : SDLK_LEFT),
    rightKey(wasd ? SDLK_d : SDLK_RIGHT),
    shootKey(wasd ? SDLK_v : SDLK_m),
    jumpPressed(false),
    spawnCommand(spawnCommand),
    spawnTime(0),
    spawnCooldown(1000),
    holdTime(-1.0f),
    maxHold(1000.0f) {
}

HeroInputComponent::~HeroInputComponent() {
    this->entity = NULL;
    if (spawnCommand) {
        delete spawnCommand;
    }
}

void HeroInputComponent::updateTime(int dt) {
    // update the spawn time
    this->spawnTime -= dt;
    if (this->spawnTime < 0) {
        this->spawnTime = 0;
    }

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
    } else if (keycode == this->rightKey) {
        this->entity->physics->accelerateX(1);
        this->entity->dir = 1;
    } else if (keycode == this->shootKey) {
        // check if enough time has passed to shoot
        if (this->spawnTime > 0) {
            return;
        }
        this->spawnTime = this->spawnCooldown;

        // check if enough ammo to shoot
        if (!this->entity->ammo->hasAmmo()) {
            return;
        }
        this->entity->ammo->spendAmmo();

        // start to charge the shot
        if (this->holdTime < 0) {
            this->holdTime = 0.0f;
        }

    } else if (keycode == SDLK_k) {
        this->entity->health->toggleInvincibility();
        this->entity->physics->toggleInfiniteJumps();
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
    } else if (keycode == this->shootKey) {
        // don't allow a shot if not charged
        if (this->holdTime <= 0) {
            return;
        }
        
        this->entity->actionState = THROW;
        this->spawnCommand->dir = this->entity->dir;
        if (this->spawnCommand->dir == 1) {
            this->spawnCommand->x = entity->x + 48;
        } else {
            this->spawnCommand->x = entity->x + 16;
        }
        this->spawnCommand->y = entity->y+20;
        this->spawnCommand->ownerID = entity->getId();
        this->spawnCommand->charge = this->holdTime / this->maxHold;
        Component::commandList->push_back(this->spawnCommand);

        // reset hold time
        this->holdTime = -1.0f;
    }
}
