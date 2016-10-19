#include "inputComponent.h"

HeroInputComponent::HeroInputComponent(Entity* entity, bool wasd, SpawnEntityCommand* spawnCommand) :
    InputComponent(entity),
    accelRate(.001f),
    maxVelocity(.6f),       // .6f
    velocityDecay(.95f),
    wasd(wasd),
    spawnCommand(spawnCommand),
    jumps(0) {
    this->entity->yAccel = .0017f;
}

HeroInputComponent::~HeroInputComponent() {
    this->entity = NULL;
    if (spawnCommand) {
        delete spawnCommand;
    }
}

float HeroInputComponent::boundVelocity(float velocity) {
    if (velocity > this->maxVelocity)
        velocity = this->maxVelocity;
    else if (velocity < -1 * this->maxVelocity)
        velocity = -1 * this->maxVelocity;
    return velocity;
}

void HeroInputComponent::keyDown(SDL_Keycode keycode) {
    if ((!this->wasd && keycode == SDLK_UP) || (this->wasd && keycode == SDLK_w)) {
        if (this->jumps < 2 && this->entity->yVelocity >= 0.0f) {
            this->entity->yVelocity = -.6f;
            this->entity->y -= 1.0f;
            this->jumps += 1;
        }
        this->entity->yAccel = -1 * this->accelRate + .0017f;
    } else if ((!this->wasd && keycode == SDLK_DOWN) || (this->wasd && keycode == SDLK_s)) {
        this->entity->yAccel = this->accelRate + .0017f;
    } else if ((!this->wasd && keycode == SDLK_LEFT) || (this->wasd && keycode == SDLK_a)) {
        this->entity->xAccel = -1 * this->accelRate;
        this->spawnCommand->dir = -1;
    } else if ((!this->wasd && keycode == SDLK_RIGHT) || (this->wasd && keycode == SDLK_d)) {
        this->entity->xAccel = this->accelRate;
        this->spawnCommand->dir = 1;
    } else if ((!this->wasd && keycode == SDLK_k) || (this->wasd && keycode == SDLK_k)) {
        this->entity->health->toggleInvincibility();
    } else if ((!this->wasd && keycode == SDLK_m) || (this->wasd && keycode == SDLK_v)) {
        this->entity->actionState = THROW;
        this->spawnCommand->x = entity->x+10;
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
                this->entity->yAccel = .0017f;   // = .0017f
                break;
            case SDLK_a:
            case SDLK_d:
                this->entity->xAccel = 0;
        }
    } else {
        switch (keycode) {
            case SDLK_UP:
            case SDLK_DOWN:
                this->entity->yAccel = .0017f;   // = .0017f
                break;
            case SDLK_LEFT:
            case SDLK_RIGHT:
                this->entity->xAccel = 0;
        }
    }
}

void HeroInputComponent::updateLocation(int dt) {
    this->entity->xVelocity += this->entity->xAccel * dt;
    this->entity->xVelocity = this->boundVelocity(this->entity->xVelocity);
    this->entity->yVelocity += this->entity->yAccel * dt;
    this->entity->yVelocity = this->boundVelocity(this->entity->yVelocity);

    this->entity->xVelocity *= this->velocityDecay;
    this->entity->yVelocity *= this->velocityDecay;

    this->entity->x += this->entity->xVelocity * dt;
    this->entity->y += this->entity->yVelocity * dt;

    if (this->entity->y > 1600)          // die if falling off screen
        this->entity->health->takeDamage(1000);  // TODO: remove!
}

void HeroInputComponent::resetJumps() {
    this->jumps = 0;
}
