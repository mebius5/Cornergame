#ifndef CORNERGAME_INPUT_COMPONENT_H
#define CORNERGAME_INPUT_COMPONENT_H

#include <SDL_keycode.h>
#include <map>
#include "entity.h"

class Entity;

class InputComponent {
protected:
    Entity * entity;

public:
    InputComponent(Entity * entity);
    virtual ~InputComponent(){};
    virtual void keyDown(SDL_Keycode keycode)=0;
    virtual void keyUp(SDL_Keycode keycode)=0;
    virtual void updateLocation(int dt)=0;
};

class HeroInputComponent: public InputComponent {
private:
    float accelRate;
    float maxVelocity;
    float velocityDecay;
    float boundVelocity(float velocity);

public:
    HeroInputComponent(Entity * entity);
    ~HeroInputComponent();
    void keyDown(SDL_Keycode keycode);
    void keyUp(SDL_Keycode keycode);
    void updateLocation(int dt);
};

class StartStateInputComponent: public InputComponent {
public:
    StartStateInputComponent(Entity * entity);
    ~StartStateInputComponent(){};
    void keyDown(SDL_Keycode keycode);
    void keyUp(SDL_Keycode keycode);
    void updateLocation(int dt);
};

class MenuStateInputComponent: public InputComponent {
public:
    MenuStateInputComponent(Entity * entity);
    ~MenuStateInputComponent(){};
    void keyDown(SDL_Keycode keycode);
    void keyUp(SDL_Keycode keycode);
    void updateLocation(int dt);
};

#endif
