#ifndef CORNERGAME_ART_COMPONENT_H
#define CORNERGAME_ART_COMPONENT_H

#include <SDL_render.h>

class ArtComponent {
public:
    int layer;
    virtual ~ArtComponent(){};
    virtual SDL_Texture * getNextTexture(int dTime) = 0;
};


class StaticArtComponent: public ArtComponent{
private:
    SDL_Texture * texture;
public:
    StaticArtComponent(SDL_Texture* texture, int layer);
    ~StaticArtComponent();
    SDL_Texture * getNextTexture(int dTime);
};

class AnimatedArtComponent: public ArtComponent{
private:
    SDL_Texture * texture;
public:
    AnimatedArtComponent(SDL_Texture* texture, int layer);
    ~AnimatedArtComponent();
    SDL_Texture * getNextTexture(int dTime);
};

#endif //CORNERGAME_ART_COMPONENT_H
