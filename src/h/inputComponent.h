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
    Command* runCommand;
    Command* stopCommand;
    SDL_Keycode upKey;
    SDL_Keycode downKey;
    SDL_Keycode leftKey;
    SDL_Keycode rightKey;
    SDL_Keycode shootKey;
    SDL_Keycode leftDodge;
    SDL_Keycode rightDodge;
    bool jumpPressed;
    float holdTime;
    float maxHold;
    bool leftPressed;
    bool rightPressed;
public:
    HeroInputComponent(Entity* entity, bool wasd);
    ~HeroInputComponent();
    void updateTime(int dt);
    void keyDown(SDL_Keycode keycode);
    void keyUp(SDL_Keycode keycode);
    void invertControl();
};

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
    bool isSelected();
    void updateTime(int dt);
    void keyDown(SDL_Keycode keycode);
    void keyUp(SDL_Keycode keycode);
};

class LevelSelectInputComponent : public InputComponent {
private:
protected:
    int index;                  // index of this menu option
    int numOptions;             // total number of menu options
    int currIndex;              // currently selected menu option
    Command* nextStateCommand;  // when space pressed, fire if selected
    bool * levelSelected;
public:
    LevelSelectInputComponent(Entity* entity, int index, int numOptions,
                              Command* nextStateCommand, bool * levelSelected);
    ~LevelSelectInputComponent();
    void updateTime(int dt);
    void keyUp(SDL_Keycode keycode);
    void keyDown(SDL_Keycode keycode);
};

#endif
