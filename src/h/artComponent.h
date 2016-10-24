#ifndef CORNERGAME_ART_COMPONENT_H
#define CORNERGAME_ART_COMPONENT_H

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <string>
#include <math.h>
#include <iostream>
#include "structs.h"
#include "entity.h"
#include "component.h"

class ArtComponent : public Component {
public:
    const static int MAXLAYER = 2;
    int layer;
    ArtComponent(Entity* entity, int layer, bool movesWithCamera);
    virtual ~ArtComponent() { };
    virtual SDL_Texture* getNextTexture(int dt) = 0;
    virtual SDL_Rect* getNextSrcRect(int dt) = 0;

    bool movesWithCamera;
    int offsetX;
    int offSetY;
};

class StaticArtComponent : public ArtComponent {
private:
    SDL_Texture* texture;
public:
    StaticArtComponent(Entity* entity, SDL_Texture* texture, int layer,
                       bool movesWithCamera);
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
};

class AnimationComponent : public ArtComponent {
private:
    SDL_Texture* texture;
    int surfaceW;
    int surfaceH;
    int timecount;
    int actionTime;
    SDL_Rect clip;
    DynamicCollisionComponent* collisionComp;
public:
    AnimationComponent(Entity* entity, Texture texture, int layer);
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
    HealthComponent* ownerHealth;
    float width;
    int height;
    int lastHealth;
public:
    HealthBarArtComponent(Entity* entity, Texture tex,
                          HealthComponent* ownerHealth, int layer);
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
};

class ScoreTextArtComponent: public ArtComponent{
private:
    ScoreComponent* ownerScore;
    SDL_Renderer* renderer;
    SDL_Texture* lastTexture;
    int lastScore;
    TTF_Font* font;
public:
    ScoreTextArtComponent(Entity* entity, SDL_Renderer* renderer, TTF_Font* font,
                          ScoreComponent* ownerScore, int layer);
    ~ScoreTextArtComponent();
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
};

#endif
