#include "inputComponent.h"

HeroInputComponent::HeroInputComponent(Entity* entity, bool wasd) :
    InputComponent(entity),
    runCommand(new PlaySoundCommand(SFX_RUNNING)),
    stopCommand(new StopSoundCommand(SFX_RUNNING)),
    upKey(wasd ? SDLK_w : SDLK_UP),
    downKey(wasd ? SDLK_s : SDLK_DOWN),
    leftKey(wasd ? SDLK_a : SDLK_LEFT),
    rightKey(wasd ? SDLK_d : SDLK_RIGHT),
    shootKey(wasd ? SDLK_v : SDLK_PERIOD),
    leftDodge(wasd ? SDLK_c : SDLK_COMMA),
    rightDodge(wasd ? SDLK_b : SDLK_SLASH),
    jumpPressed(false),
    holdTime(-1.0f),
    maxHold(500.0f),
    leftPressed(false),
    rightPressed(false) {
}

HeroInputComponent::~HeroInputComponent() {
    this->entity = NULL;
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
    // see if we're holding down a key
    if (this->leftPressed) {
        this->entity->physics->accelerateX(-1);
        if (this->runCommand && dynamic_cast<HeroCollisionComponent*>(this->entity->collision)->onGround)
            Component::commandList->push_back(this->runCommand);
    }
    if (this->rightPressed) {
        this->entity->physics->accelerateX(1);
        if (this->runCommand && dynamic_cast<HeroCollisionComponent*>(this->entity->collision)->onGround)
            Component::commandList->push_back(this->runCommand);
    }
}

void HeroInputComponent::keyDown(SDL_Keycode keycode) {
    if (this->entity->physics->dodgeTime < 0) {
        if (keycode == this->upKey) {
            if (!this->jumpPressed) {
                this->entity->physics->jump();
                this->jumpPressed = true;
            }
            this->entity->physics->accelerateY(-1);
        } else if (keycode == this->downKey) {
            this->entity->physics->accelerateY(1);
        } else if (keycode == this->leftKey) {
            this->entity->physics->accelerateX(-1);
            if (this->runCommand && dynamic_cast<HeroCollisionComponent*>(this->entity->collision)->onGround)
                Component::commandList->push_back(this->runCommand);
            this->leftPressed = true;
        } else if (keycode == this->rightKey) {
            this->entity->physics->accelerateX(1);
            if (this->runCommand && dynamic_cast<HeroCollisionComponent*>(this->entity->collision)->onGround)
                Component::commandList->push_back(this->runCommand);
            this->rightPressed = true;
        } else if (keycode == this->shootKey) {
            // start to charge the shot
            if (this->holdTime < 0) {
                this->holdTime = 0.0f;
            }
        } else if (keycode == this->leftDodge) {
            this->entity->physics->dodge(-1);
            this->entity->particle->startSpawning(300, 400);
        } else if (keycode == this->rightDodge) {
            this->entity->physics->dodge(1);
            this->entity->particle->startSpawning(300, 400);
        }
    }

    if (keycode == SDLK_k) {
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
    } else if (keycode == this->downKey) {
        this->entity->physics->clearAccelerationY();
    } else if (keycode == this->leftKey || keycode == this->rightKey) {
        if (keycode == this->leftKey)
            this->leftPressed = false;
        if (keycode == this->rightKey)
            this->rightPressed = false;
        this->entity->physics->clearAccelerationX();
        if (this->stopCommand)
            Component::commandList->push_back(this->stopCommand);
    } else if (keycode == this->shootKey) {
        if (this->entity->physics->dodgeTime >= 0)
            return;
        // don't allow a shot if not charged
        if (this->holdTime <= 0) {
            return;
        }
        this->entity->ammo->spendAmmo(this->holdTime / this->maxHold);

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

    tempKey = this->leftDodge;
    this->leftDodge = this->rightDodge;
    this->rightDodge = tempKey;
}
