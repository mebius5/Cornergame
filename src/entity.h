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

class Sprite : public Entity{

};

class Pickup : public Sprite{

};

class Projectile : public Sprite {

};

class Character: public Sprite {

};

class Player : public Character {

};

class Hero: public Player {

private:
public:
    Hero(int startX, int startY, int width, int height);
    ~Hero();
};

class Enemy : public Character {
public:
    Enemy();
    ~Enemy();
}

class Terrain : public Entity{

};

class Background : public Entity{

};

#endif //CORNERGAME_ENTITY_H
