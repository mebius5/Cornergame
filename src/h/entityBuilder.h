#ifndef CORNERGAME_ENTITY_BUILDER_H
#define CORNERGAME_ENTITY_BUILDER_H

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include "enums.h"
#include "entity.h"

class EntityBuilder {
private:
    int nextId;
    SDL_Renderer* renderer;
    SDL_Surface * loadImage(const char * filename);
    SDL_Surface* loadFont(const char * fontName,
                          const char * text,
                          int fontSize,
                          int r, int g, int b, int initialAlpha);
public:
    EntityBuilder(SDL_Renderer* renderer);
    Entity * createHero(int x, int y, const char* collisionSfxFile);
    Entity * createEnemy(int x, int y);
    Entity * createBackground(const char * filename, int width, int height);
    Entity * createHealthBar(int x, int y, int width, int height, Entity * owner);
    Entity * createScoreBox(int x, int y, Entity * owner);
    Entity * createCenteredFadeInText(const char *fontName,
                                      const char *text,
                                      int fontSize,
                                      int r, int g, int b, int initialAlpha,
                                      int windowW, int windowH);
    Entity * createHorizontallyCenteredFadeInText(const char *fontName,
                                      const char *text,
                                      int fontSize,
                                      int r, int g, int b, int initialAlpha,
                                      int windowW, int yPos,
                                      int index, int numOptions,
                                      StateEnum nextState);
};

#endif
