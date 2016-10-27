#ifndef CORNERGAME_POWERUPCOMPONENT_H
#define CORNERGAME_POWERUPCOMPONENT_H

#include "entity.h"
#include "component.h"

class PowerUpComponent : public Component {
private:
    int timeElapsed;
    bool infiniteJumpActivated;
public:
    PowerUpComponent(Entity * owner);
    void update(int dt);
    void activateInfiniteJumpsPowerUp();
    void deactivateInfiniteJumpsPowerUp();
};

#endif //CORNERGAME_POWERUPCOMPONENT_H
