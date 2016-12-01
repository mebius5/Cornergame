#ifndef CORNERGAME_ENTITY_BUILDER_H
#define CORNERGAME_ENTITY_BUILDER_H

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "consts.h"
#include "entity.h"

class EntityBuilder {
private:
    int nextId;
    SDL_Renderer* renderer;
    std::vector<Texture> textureMap;
    std::vector<std::vector<Texture>> terrainTexMap;  // indexes by type & width
    std::vector<std::vector<TTF_Font*>> fontMap;      // indexes by font & size
    SDL_Surface* createTextSurface(FontEnum font, const char *text, int fontSize,
                                   int r, int g, int b, int a, int windowW);
    SDL_Surface* loadImage(const char* filename);
public:
    EntityBuilder(SDL_Renderer *renderer);
    void loadTexture(TextureEnum texType, const char* filename);
    void loadHealthBar(int width, int height);
    void loadAmmoBar(int width, int height);
    void loadFont(FontEnum fontType, int fontSize);
    void loadTerrain(TerrainTexEnum texType, int width);
    void freeTextures();
    void freeFonts();
    Entity* createHero(TextureEnum texType, int x, int y, SfxEnum sfxType, bool wasd);
    Entity* createEnemy(TextureEnum texType, int x, int y, std::vector<Entity*>* heroes);
    Entity* createBackground(TextureEnum texType, int x, int y, float speed);
    Entity* createHealthBar(int x, int y, Entity* owner);
    Entity* createAmmoBar(int x, int y, Entity* owner);
    // Entity* createScoreBox(int x, int y, Entity* owner, FontEnum font, int fontSize);

    Entity* createFadeInText(FontEnum fontType, const char *text, int fontSize,
                             int r, int g, int b, int initialAlpha,
                             int windowW, int x, int y);
    Entity* createHorizontallyCenteredFadeInMenuText(FontEnum fontType,
                                                     const char *text, int fontSize,
                                                     int r, int g, int b, int initialAlpha,
                                                     int windowW, int yPos,
                                                     int index, int numOptions,
                                                     StateEnum nextState);

    Entity* createLevelPreview(TextureEnum tex, int x, int y);
    Entity* createVictoryZone(int x, int y);
    Entity* createPowerUp(TextureEnum pwrUpType, SfxEnum pwrSound, int x, int y);
    Entity* createPowerUpOverlay(TextureEnum pwrUpType, int x, int y, Entity * owner, int index);
    Entity* createStaticBackgroundObject(TextureEnum texType, int x, int y) ;
    Entity* createStaticBackgroundObject(TextureEnum texType, TextureEnum lightType, int x, int y);
    Entity* createTerrain(TerrainTexEnum texType, int x, int y, int numberHorizontal,
            bool freeTop, bool freeBot, bool freeRight, bool freeLeft);
    Entity* createBounce(TextureEnum tileType, int x, int y);
    Entity* createFadingTerrain(TerrainTexEnum texType, int x, int y, int numberHorizontal,
                          bool freeTop, bool freeBot, bool freeRight, bool freeLeft);
    Entity* createProjectile(TextureEnum texType, int x, int y, float charge, int dir, int ownerID, Entity * closest);
};

#endif
