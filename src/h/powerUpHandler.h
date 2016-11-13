#ifndef CORNERGAME_POWERUP_HANDLER_H
#define CORNERGAME_POWERUP_HANDLER_H

#include "powerUpComponent.h"

class PowerUpHandler {
private:
    std::vector<PowerUpComponent*>& componentList;
public:
    PowerUpHandler(std::vector<PowerUpComponent*>& componentList);
    void update(int dt);
};

#endif
