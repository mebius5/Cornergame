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
    virtual void updateTime(int dt) = 0;
    virtual void keyDown(SDL_Keycode keycode) = 0;
    virtual void keyUp(SDL_Keycode keycode) = 0;
};

class HeroInputComponent: public InputComponent {
private:
    SDL_Keycode upKey;
    SDL_Keycode downKey;
    SDL_Keycode leftKey;
    SDL_Keycode rightKey;
    SDL_Keycode shootKey;
    bool jumpPressed;
    SpawnEntityCommand* spawnCommand;
    int spawnTime;
    int spawnCooldown;
    float holdTime;
    float maxHold;
public:
    HeroInputComponent(Entity* entity, bool wasd, SpawnEntityCommand* spawnCommand);
    ~HeroInputComponent();
    void updateTime(int dt);
    void keyDown(SDL_Keycode keycode);
    void keyUp(SDL_Keycode keycode);
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
    void updateTime(int dt);
    void keyDown(SDL_Keycode keycode);
    void keyUp(SDL_Keycode keycode);
};

#endif
