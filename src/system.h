//
// Created by Grady Xiao on 9/21/16.
//

#ifndef CORNERGAME_SYSTEM_H
#define CORNERGAME_SYSTEM_H

#include <list>
#include "entity.h"

class System {

};

class Drawer : public System {
private:
    SDL_Renderer * renderer;
public:
    Drawer(SDL_Renderer * renderer);
    void draw(std::list<Entity> * entityList);
};

class CollisionDetector : public System {

};

class LocationCalculator : public System {

};

class InputHandler : public System {

};

class SoundHandler : public System {

};

#endif //CORNERGAME_SYSTEM_H
