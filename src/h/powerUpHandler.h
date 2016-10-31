
#ifndef CORNERGAME_POWERUPHANDLER_H
#define CORNERGAME_POWERUPHANDLER_H

#include "powerUpComponent.h"

class PowerUpHandler {
private:
    std::vector<PowerUpComponent*>& componentList;
public:
    PowerUpHandler(std::vector<PowerUpComponent*>& componentList);
    void update(int dt);
};

#endif //CORNERGAME_POWERUPHANDLER_H
