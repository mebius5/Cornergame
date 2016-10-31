#ifndef CORNERGAME_POWERUPCOMPONENT_H
#define CORNERGAME_POWERUPCOMPONENT_H

#include "entity.h"
#include "component.h"

//Must include entity.h before component.h

class PowerUpComponent : public Component {
private:
    int timeElapsed;
    bool infJumpActivated;
    bool infHealthActivated;
public:
    PowerUpComponent(Entity * owner);
    void update(int dt);
    void activateInfJumpPwrUp();
    void deactivateInfJumpPwrUp();
    void activateInfHealthPwrUp();
    void deactivateInfHealthPwrUp();
};

#endif //CORNERGAME_POWERUPCOMPONENT_H
