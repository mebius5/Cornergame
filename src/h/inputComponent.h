#ifndef CORNERGAME_INPUT_COMPONENT_H
#define CORNERGAME_INPUT_COMPONENT_H

#include <SDL_keycode.h>
#include <map>
#include "entity.h"
#include "component.h"

class InputComponent : public Component {
public:
    InputComponent(Entity* entity);
    virtual ~InputComponent() { };
    virtual void keyDown(SDL_Keycode keycode) = 0;
    virtual void keyUp(SDL_Keycode keycode) = 0;
    virtual void updateLocation(int dt) = 0;
};

class HeroInputComponent: public InputComponent {
private:
    float accelRate;
    float maxVelocity;
    float velocityDecay;
    float boundVelocity(float velocity);
    bool wasd;

public:
    HeroInputComponent(Entity* entity, bool wasd);
    ~HeroInputComponent();
    void keyDown(SDL_Keycode keycode);
    void keyUp(SDL_Keycode keycode);
    void updateLocation(int dt);
};

// class StartScreenInputComponent : public InputComponent {
// public:
//     StartScreenInputComponent(Entity* entity);
//     ~StartScreenInputComponent();
//     void keyDown(SDL_Keycode keycode);
//     void keyUp(SDL_Keycode keycode);
//     void update(int dt);
// };

class MenuOptionInputComponent : public InputComponent {
private:
    int index;                  // index of this menu option
    int numOptions;             // total number of menu options
    int currIndex;              // currently selected menu option
    bool selected;              // is this option selected
    Command* nextStateCommand;  // when space pressed, fire if selected
public:
    MenuOptionInputComponent(Entity* entity, int index, int numOptions,
                             Command* nextStateCommand);
    ~MenuOptionInputComponent();
    void keyDown(SDL_Keycode keycode);
    void keyUp(SDL_Keycode keycode);
    void updateLocation(int dt);
};

#endif
