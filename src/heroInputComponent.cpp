#include "inputComponent.h"

HeroInputComponent::HeroInputComponent(Entity* entity) :
        InputComponent(entity),
        accelRate(.001f),
        maxVelocity(.4f),
        velocityDecay(.95f) {
}

HeroInputComponent::~HeroInputComponent() {
    this->entity = NULL;
}

float HeroInputComponent::boundVelocity(float velocity) {
    if (velocity > this->maxVelocity)
        velocity = this->maxVelocity;
    else if (velocity < -1 * this->maxVelocity)
        velocity = -1 * this->maxVelocity;
    return velocity;
}

Command* HeroInputComponent::keyDown(SDL_Keycode keycode) {
    switch (keycode) {
        case SDLK_UP:
            this->entity->yAccel = -1 * this->accelRate;
            break;
        case SDLK_DOWN:
            this->entity->yAccel = this->accelRate;
            break;
        case SDLK_LEFT:
            this->entity->xAccel = -1 * this->accelRate;
            break;
        case SDLK_RIGHT:
            this->entity->xAccel = this->accelRate;
    }
    return NULL;
}

Command* HeroInputComponent::keyUp(SDL_Keycode keycode) {
    switch (keycode) {
        case SDLK_UP:
        case SDLK_DOWN:
            this->entity->yAccel = 0;
            break;
        case SDLK_LEFT:
        case SDLK_RIGHT:
            this->entity->xAccel = 0;
    }
    return NULL;
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
}
