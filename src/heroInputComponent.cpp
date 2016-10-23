#include "inputComponent.h"

HeroInputComponent::HeroInputComponent(Entity* entity, bool wasd, SpawnEntityCommand* spawnCommand) :
    InputComponent(entity),
    wasd(wasd),
    spawnCommand(spawnCommand) {
}

HeroInputComponent::~HeroInputComponent() {
    this->entity = NULL;
    if (spawnCommand) {
        delete spawnCommand;
    }
}

void HeroInputComponent::keyDown(SDL_Keycode keycode) {
    if ((!this->wasd && keycode == SDLK_UP) || (this->wasd && keycode == SDLK_w)) {
        this->entity->physics->jump();
        this->entity->physics->accelerateY(-1);
    } else if ((!this->wasd && keycode == SDLK_DOWN) || (this->wasd && keycode == SDLK_s)) {
        this->entity->physics->accelerateY(1);
    } else if ((!this->wasd && keycode == SDLK_LEFT) || (this->wasd && keycode == SDLK_a)) {
        this->entity->physics->accelerateX(-1);
        this->spawnCommand->dir = -1;
    } else if ((!this->wasd && keycode == SDLK_RIGHT) || (this->wasd && keycode == SDLK_d)) {
        this->entity->physics->accelerateX(1);
        this->spawnCommand->dir = 1;
    } else if ((!this->wasd && keycode == SDLK_k) || (this->wasd && keycode == SDLK_k)) {
        this->entity->health->toggleInvincibility();
        this->entity->physics->toggleInfiniteJumps();
    } else if ((!this->wasd && keycode == SDLK_m) || (this->wasd && keycode == SDLK_v)) {
        this->entity->actionState = THROW;
        if (this->spawnCommand->dir == 1) {
            this->spawnCommand->x = entity->x + entity->width;
        } else {
            this->spawnCommand->x = entity->x;
        }
        this->spawnCommand->y = entity->y+20;
        this->spawnCommand->ownerID = entity->getId();
        Component::commandList->push_back(this->spawnCommand);
    }

}

void HeroInputComponent::keyUp(SDL_Keycode keycode) {
    if(wasd){
        switch (keycode) {
            case SDLK_w:
            case SDLK_s:
                this->entity->physics->clearAccelerationY();
                break;
            case SDLK_a:
            case SDLK_d:
                this->entity->physics->clearAccelerationX();
        }
    } else {
        switch (keycode) {
            case SDLK_UP:
            case SDLK_DOWN:
                this->entity->physics->clearAccelerationY();
                break;
            case SDLK_LEFT:
            case SDLK_RIGHT:
                this->entity->physics->clearAccelerationX();
        }
    }
}
