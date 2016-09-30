#ifndef CORNERGAME_ART_COMPONENT_H
#define CORNERGAME_ART_COMPONENT_H

#include <SDL_render.h>

class ArtComponent {
public:
    int layer;
    virtual ~ArtComponent() { };
    virtual SDL_Texture* getNextTexture(int dt) = 0;
};

class StaticArtComponent : public ArtComponent {
private:
    SDL_Texture* texture;
public:
    StaticArtComponent(SDL_Texture* texture, int layer);
    ~StaticArtComponent();
    SDL_Texture* getNextTexture(int dt);
};

class AnimationComponent : public ArtComponent {
private:
    SDL_Texture* texture;
public:
    AnimationComponent(SDL_Texture* texture, int layer);
    ~AnimationComponent();
    SDL_Texture* getNextTexture(int dt);
};

#endif
