#ifndef CORNERGAME_POWERUP_COMPONENT_H
#define CORNERGAME_POWERUP_COMPONENT_H

#include "entity.h"
#include "component.h"

// NOTE: REFER TO PowerUpEnums in the enums.h

class PowerUpComponent : public Component {
private:
    int pwrUpTimerArraySize;
public:
    int pwrUPTimerArray[4]; //Change the array size based on the number of PowerUpEnums
    PowerUpComponent(Entity * owner);
    void update(int dt);
    void activatePowerUp(TextureEnum pwrUpType);
    void activateInfJumpPwrUp();
    void deactivateInfJumpPwrUp();
    void activateInfHealthPwrUp();
    void deactivateInfHealthPwrUp();
    void activateIncreaseAmmo();
    void activateBeerPwrUp();
    void deactivateBeerPwrUp();
};

#endif
