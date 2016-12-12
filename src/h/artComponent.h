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
protected:
    Texture * lightTexture;
public:
    LayerEnum layer;
    bool movesWithCamera;
    float offsetX;
    float offsetY;
    bool isVisible;
    bool globalLighting;

    ArtComponent(Entity* entity, LayerEnum layer, bool movesWithCamera);
    virtual ~ArtComponent(){};
    virtual void updateLocation() {};      // for ArtComponents with owners
    virtual SDL_Texture* getNextTexture(int dt) = 0;
    virtual SDL_Rect* getNextSrcRect(int dt) = 0;
    virtual double getNextAngle(int /*dt*/){return 0;};
    virtual SDL_RendererFlip  getNextFlip(int /*dt*/){return SDL_FLIP_NONE;};
    Texture * getLightTexture();
    void setLightTexture(Texture *lightTexture, bool addTrueModFalse);
};

class StaticArtComponent : public ArtComponent {
protected:
    SDL_Texture* texture;
public:
    StaticArtComponent(Entity* entity, SDL_Texture* texture, LayerEnum layer,
                       bool movesWithCamera);
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
    SDL_RendererFlip getNextFlip(int dt);
};

class ObjectAnimationComponent : public ArtComponent {
private:
    SDL_Texture* texture;
    int timecount;
    int fps;
    int numFrames;
    SDL_Rect clip;
public:
    ObjectAnimationComponent(Entity* entity, SDL_Texture* texture, LayerEnum layer, bool movesWithCamera, int fps, int numFrames);
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);

};

class AnimationComponent : public ArtComponent {
protected:
    SDL_Texture* texture;
    int surfaceW;
    int surfaceH;
    int timecount;
    SDL_Rect clip;
    DynamicCollisionComponent* collisionComp;
public:
    int actionTime;
    AnimationComponent(Entity* entity, Texture texture, LayerEnum layer);
    virtual SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
    double getNextAngle(int dt);
    SDL_RendererFlip  getNextFlip(int dt);
};

class OneTimeAnimationComponent : public AnimationComponent {
private:
    Command* despawnCommand;
    int animationTime;
    Texture animationTex;
    bool started;
    bool ended;
public:
    ~OneTimeAnimationComponent();
    OneTimeAnimationComponent(Entity* entity, Texture texture, LayerEnum layer,
                              int animationTime);
    void startAnimation();
    SDL_Rect* getNextSrcRect(int dt);
};

class BounceAnimationComponent : public AnimationComponent {
public:
    BounceAnimationComponent(Entity* entity, Texture texture);
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
    void restartAnimation();
};

class ProjectileArtComponent : public ArtComponent {
private:
    SDL_Texture* texture;
public:
    ProjectileArtComponent(Entity* entity, SDL_Texture* texture);
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
    double getNextAngle(int dt);
    SDL_RendererFlip  getNextFlip(int dt);
};


class ParticleAnimationComponent : public AnimationComponent {
private:
    Command* despawnCommand;
    int counter;
    int lastDraw;
public:
    ParticleAnimationComponent(Entity* entity, Texture texture);
    ~ParticleAnimationComponent();
    void updateLocation();
    SDL_Texture* getNextTexture(int dt);
    SDL_Rect* getNextSrcRect(int dt);
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
    void resetComponent();
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
    SDL_RendererFlip  getNextFlip(int dt);

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
//    double getNextAngle(int dt);
//    SDL_RendererFlip  getNextFlip(int dt);
// };

#endif
