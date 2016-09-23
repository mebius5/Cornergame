//
// Created by Grady Xiao on 9/21/16.
//

#ifndef CORNERGAME_ENTITY_H
#define CORNERGAME_ENTITY_H

#include "component.h"

class Entity{

private:
    int id;

public:
    Location * location;
    Health * health;
    Physics * physics;
    Texture * texture;
    Input * input;
};

class Sprite : Entity{

};

class Pickup : Sprite{

};

class Projectile : Sprite {

};

class Character: Sprite {

};

class Player : Character {

};

class Hero: public Player {

private:
public:
    Hero(int startX, int startY, SDL_Texture * texture);
    ~Hero();
};

class Terrain : Entity{

};

class Background : Entity{

};

#endif //CORNERGAME_ENTITY_H
