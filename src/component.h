//
// Created by Grady Xiao on 9/23/16.
//

#ifndef CORNERGAME_PLUGIN_H
#define CORNERGAME_PLUGIN_H


#include <SDL_render.h>
#include "command.h"

class Component {

};

class Location : public Component {
public:
    int xPixel;
    int yPixel;
    int width;
    int height;
    Location(int x, int y, int width, int height);
};

class Health: public Component {

};

class Physics : public Component{

};

class Texture : public Component{
public:
    SDL_Texture * texture;
    int layer;
    Texture(SDL_Texture * texture, int layer);
};

class Input : public Component {
public:
    Command * onLeft;
    Command * onRight;
    Command * onUp;
    Command * onDown;
};

#endif //CORNERGAME_PLUGIN_H
