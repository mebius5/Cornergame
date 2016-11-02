#ifndef CORNERGAME_POWERUPCOMPONENT_H
#define CORNERGAME_POWERUPCOMPONENT_H

#include "entity.h"
#include "component.h"

//Must include entity.h before component.h


//REFER TO PowerUpEnums in the enums.h

class PowerUpComponent : public Component {
private:
    int pwrUpTimerArraySize;
    int pwrUPTimerArray[3]; //Change the array size based on the number of PowerUpEnums
public:
    PowerUpComponent(Entity * owner);
    void update(int dt);
    void activatePowerUp(PowerUpType pwrUpType);
    void activateInfJumpPwrUp();
    void deactivateInfJumpPwrUp();
    void activateInfHealthPwrUp();
    void deactivateInfHealthPwrUp();
    void activateIncreaseAmmo();
};

#endif //CORNERGAME_POWERUPCOMPONENT_H
