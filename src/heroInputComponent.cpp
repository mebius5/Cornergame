#include "inputComponent.h"

HeroInputComponent::HeroInputComponent(Entity* entity, bool wasd, SpawnEntityCommand* spawnCommand) :
    InputComponent(entity),
    upKey(wasd ? SDLK_w : SDLK_UP),
    downKey(wasd ? SDLK_s : SDLK_DOWN),
    leftKey(wasd ? SDLK_a : SDLK_LEFT),
    rightKey(wasd ? SDLK_d : SDLK_RIGHT),
    shootKey(wasd ? SDLK_v : SDLK_m),
    jumpPressed(false),
    spawnCommand(spawnCommand) {
}

HeroInputComponent::~HeroInputComponent() {
    this->entity = NULL;
    if (spawnCommand) {
        delete spawnCommand;
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
        this->entity->actionState = THROW;
        this->spawnCommand->dir = this->entity->dir;
        if (this->spawnCommand->dir == 1) {
            this->spawnCommand->x = entity->x + 48;
        } else {
            this->spawnCommand->x = entity->x + 16;
        }
        this->spawnCommand->y = entity->y+20;
        this->spawnCommand->ownerID = entity->getId();
        Component::commandList->push_back(this->spawnCommand);
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
    }
}
