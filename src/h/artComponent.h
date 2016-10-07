#ifndef CORNERGAME_ART_COMPONENT_H
#define CORNERGAME_ART_COMPONENT_H

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <string>
#include <math.h>
#include <iostream>
#include "entity.h"
#include "component.h"

class ArtComponent : public Component {
public:
    const static int MAXLAYER = 2;
    int layer;
    ArtComponent(Entity* entity, int layer);
    virtual ~ArtComponent() { };
    virtual SDL_Texture* getNextTexture(int dt) = 0;
    virtual SDL_Rect* getNextSrcRect(int dt) = 0;
};

class StaticArtComponent : public ArtComponent {
private:
    SDL_Texture* texture;
public:
    StaticArtComponent(Entity* entity, SDL_Texture* texture, int layer);
    ~StaticArtComponent();
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
};

class AnimationComponent : public ArtComponent {
private:
    SDL_Texture* texture;
    int surfaceW;
    int surfaceH;
    int timecount;
    SDL_Rect clip;
public:
    AnimationComponent(Entity* entity, SDL_Texture* texture, int surfaceW,
                       int surfaceH, int layer);
    ~AnimationComponent();
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
};

class TextFadeInComponent : public ArtComponent {
private:
    SDL_Surface* surface;
    SDL_Renderer* renderer;
    SDL_Texture* lastTexture;
    double alpha;
public:
    TextFadeInComponent(Entity* entity, SDL_Renderer* renderer,
                        SDL_Surface* surface, int layer, int initialAlpha);
    ~TextFadeInComponent();
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);

    void selectMenuItem();
    void deselectMenuItem();
};

class HealthBarArtComponent: public ArtComponent {
private:
    SDL_Texture* texture;
    SDL_Rect clip;
    Entity* owner;
    float width;
    int height;
    int lastHealth;
public:
    HealthBarArtComponent(Entity* entity, SDL_Texture *texture, Entity *owner,
                          int layer, float width, int height);
    ~HealthBarArtComponent();
    SDL_Texture * getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
};

class ScoreTextArtComponent: public ArtComponent{
private:
    Entity * owner;
    SDL_Renderer * renderer;
    SDL_Texture * lastTexture;
    int lastScore;

    SDL_Surface* loadFont(const char * fontName,
                          const char * text,
                          int fontSize,
                          int r, int g, int b);
public:
    ScoreTextArtComponent(Entity* entity, SDL_Renderer* renderer, Entity* owner,
                          int layer);
    ~ScoreTextArtComponent();
    SDL_Texture * getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
};

#endif
