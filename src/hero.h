//
// Created by Grady Xiao on 9/21/16.
//

#ifndef CORNERGAME_HERO_H
#define CORNERGAME_HERO_H

#include "entity.h"
#include "component.h"

class Hero: public Player {

private:
    Location location;
    Health health;

public:
    Hero();
    ~Hero();
};

#endif //CORNERGAME_HERO_H
