#ifndef CORNERGAME_INPUT_COMPONENT_H
#define CORNERGAME_INPUT_COMPONENT_H

#include <SDL_keycode.h>
#include <map>
#include "entity.h"

class Entity;

class InputComponent {
private:
    Entity* entity;
    float accelRate;
    float maxVelocity;
    float velocityDecay;

    float boundVelocity(float velocity);
public:
    InputComponent(Entity* entity);
    void keyDown(SDL_Keycode keycode);
    void keyUp(SDL_Keycode keycode);
    void updateLocation(int dt);
};

#endif
