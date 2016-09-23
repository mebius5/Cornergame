//
// Created by Grady Xiao on 9/23/16.
//

#ifndef CORNERGAME_PLUGIN_H
#define CORNERGAME_PLUGIN_H


class Component {

};

class Location : public Component {
public:
    int xPixel;
    int yPixel;
    int width;
    int height;
    Location(int x, int y);
};

class Health: public Component {

};

class Physics : public Component{

};

class Texture : public Component{
    Texture texture;
};

class Input : public Component {
public:
    enum Direction {up, down, left, right};
};

#endif //CORNERGAME_PLUGIN_H
