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
    const static int MAXLAYER = 3;
    int layer;
    bool movesWithCamera;
    int offsetX;
    int offsetY;
    bool isVisible;

    ArtComponent(Entity* entity, int layer, bool movesWithCamera);
    virtual ~ArtComponent() { };
    virtual void updateLocation() { };      // for ArtComponents with owners
    virtual SDL_Texture* getNextTexture(int dt) = 0;
    virtual SDL_Rect* getNextSrcRect(int dt) = 0;

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

class BackgroundArtComponent : public ArtComponent {
private:
    SDL_Texture* texture;
public:
    float speed;
    BackgroundArtComponent(Entity* entity, SDL_Texture* texture, int layer, float speed);
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
};

class PowerUpArtComponent : public ArtComponent {
private:
    SDL_Texture* texture;
    PowerUpComponent* powerUp;
    int index;
    int timecount;
    SDL_Rect clip;
public:
    PowerUpArtComponent(Entity* entity, Entity* owner, Texture tex, int layer, int index);
    void updateLocation();
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
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
    HealthBarArtComponent(Entity* entity, Entity* owner, Texture tex, int layer);
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
};

class AmmoBarArtComponent: public ArtComponent {
private:
    SDL_Texture* texture;
    AmmoComponent* ownerAmmo;
    SDL_Rect clip;
    float width;
    int height;
public:
    AmmoBarArtComponent(Entity* entity, Entity* owner, Texture tex, int layer);
    void updateLocation();
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
};

class TextFadeInComponent : public ArtComponent {
private:
    SDL_Surface* surface;
    SDL_Renderer* renderer;
    SDL_Texture* lastTexture;
    float alpha;
public:
    TextFadeInComponent(Entity* entity, SDL_Renderer* renderer,
                        SDL_Surface* surface, int layer, float initialAlpha);
    ~TextFadeInComponent();
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);

    void selectMenuItem();
    void deselectMenuItem();
};

// class ScoreTextArtComponent: public ArtComponent {
// private:
//     ScoreComponent* ownerScore;
//     SDL_Renderer* renderer;
//     SDL_Texture* lastTexture;
//     int lastScore;
//     TTF_Font* font;
// public:
//     ScoreTextArtComponent(Entity* entity, SDL_Renderer* renderer, TTF_Font* font,
//                           ScoreComponent* ownerScore, int layer);
//     ~ScoreTextArtComponent();
//     SDL_Texture* getNextTexture(int dt);
//     SDL_Rect* getNextSrcRect(int dt);
// };

#endif
