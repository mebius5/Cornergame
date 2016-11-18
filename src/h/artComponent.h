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
    LayerEnum layer;
    bool movesWithCamera;
    int offsetX;
    int offsetY;
    bool isVisible;

    ArtComponent(Entity* entity, LayerEnum layer, bool movesWithCamera);
    virtual ~ArtComponent() { };
    virtual void updateLocation() { };      // for ArtComponents with owners
    virtual SDL_Texture* getNextTexture(int dt) = 0;
    virtual SDL_Rect* getNextSrcRect(int dt) = 0;
};

class StaticArtComponent : public ArtComponent {
protected:
    SDL_Texture* texture;
public:
    StaticArtComponent(Entity* entity, SDL_Texture* texture, LayerEnum layer,
                       bool movesWithCamera);
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
};

class AnimationComponent : public ArtComponent {
protected:
    SDL_Texture* texture;
    int surfaceW;
    int surfaceH;
    int timecount;
    int actionTime;
    SDL_Rect clip;
    DynamicCollisionComponent* collisionComp;
public:
    AnimationComponent(Entity* entity, Texture texture, LayerEnum layer);
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
};

class BounceAnimationComponent : public AnimationComponent {
public:
    BounceAnimationComponent(Entity* entity, Texture texture);
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
    void restartAnimation();
};

class BackgroundArtComponent : public ArtComponent {
private:
    SDL_Texture* texture;
public:
    float speed;
    BackgroundArtComponent(Entity* entity, SDL_Texture* texture, float speed);
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
    PowerUpArtComponent(Entity* entity, Entity* owner, Texture tex, LayerEnum layer, int index);
    void updateLocation();
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
};

class FadingTerrainArtComponent : public ArtComponent {
private:
    SDL_Texture* texture;
    int shakeTime;
    int maxShakeTime;
public:
    FadingTerrainArtComponent(Entity* entity, SDL_Texture* texture);
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
    void startShake();
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
    HealthBarArtComponent(Entity* entity, Entity* owner, Texture tex);
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
    AmmoBarArtComponent(Entity* entity, Entity* owner, Texture tex);
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
                        SDL_Surface* surface, float initialAlpha);
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
