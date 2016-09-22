//
// Created by Grady Xiao on 9/21/16.
//

#ifndef CORNERGAME_ENTITY_H
#define CORNERGAME_ENTITY_H

class Entity{
private:
    int id;
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

class Terrain : Entity{

};

class Background : Entity{

};

#endif //CORNERGAME_ENTITY_H
