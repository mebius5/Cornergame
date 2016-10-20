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
    if(wasd){
        switch (keycode) {
            case SDLK_w:
                this->entity->physics->jump();
                this->entity->physics->accelerateY(-1);
                break;
            case SDLK_s:
                this->entity->physics->accelerateY(1);
                break;
            case SDLK_a:
                this->entity->physics->accelerateX(-1);
                break;
            case SDLK_d:
                this->entity->physics->accelerateX(1);
                break;
            case SDLK_k:
                this->entity->health->toggleInvincibility();
                break;
        }
    }else{
        switch (keycode) {
            case SDLK_UP:
                this->entity->physics->jump();
                this->entity->physics->accelerateY(-1);
                break;
            case SDLK_DOWN:
                this->entity->physics->accelerateY(1);
                break;
            case SDLK_LEFT:
                this->entity->physics->accelerateX(-1);
                this->spawnCommand->dir = -1;
                break;
            case SDLK_RIGHT:
                this->entity->physics->accelerateX(1);
                this->spawnCommand->dir = 1;
                break;
            case SDLK_k:
                this->entity->health->toggleInvincibility();
                break;
            case SDLK_x:
                this->entity->actionState = THROW;
                this->spawnCommand->x = entity->x+10;
                this->spawnCommand->y = entity->y+20;
                Component::commandList->push_back(this->spawnCommand);
                break;
        }
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
