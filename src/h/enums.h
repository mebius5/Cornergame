#ifndef CORNERGAME_ENUMS_H
#define CORNERGAME_ENUMS_H

enum Tile {
    // Put texture enums first to match with TerrainTexEnum
    TILE_BRICK, TILE_GRASS, TILE_DIRT, TILE_NONE,
    // Other tiles
    TILE_SPAWN1, TILE_SPAWN2, TILE_ENEMY, TILE_GOAL,
    TILE_PU_JUMP, TILE_PU_HEALTH, TILE_PU_AMMO, TILE_PU_BEER,
    TILE_TREE1, TILE_TREE2, TILE_BENCH, TILE_FADEINTEXT, TILE_NORMALTEXT };

enum ActionEnum { ACTION_IDLE, ACTION_JUMP, ACTION_THROW, ACTION_DAMAGE,
                  ACTION_SLIDING };

// NOTE: keep NONE state the last one to make array indexing easier!
enum StateEnum { STATE_QUIT, STATE_START, STATE_PLAY, STATE_LEVEL_TRANSIT,
                 STATE_TUTORIAL, STATE_MENU, STATE_HIGHSCORE, STATE_RESULTS,
                 STATE_NONE };

enum ProjEnum { PROJ_HERO, PROJ_ENEMY };

// NOTE: if updating any of the following, MAKE SURE to update vector sizes in
// soundHander or entityBuilder for the map vectors.
enum SfxEnum { SFX_ALERT, SFX_AMMO, SFX_ARMOR, SFX_DRINK, SFX_JUMP,
               SFX_LAND, SFX_ENEMY, SFX_RUMBLE, SFX_RUNNING, SFX_SCRAPE,
               SFX_WOOSH, SFX_NONE };

enum MusicEnum { MUSIC_START, MUSIC_MENU, MUSIC_PLAY, MUSIC_HIGHSCORE };

enum TextureEnum {
    // List the powerups in order of its corresponding position in the array
    TEX_PWRUP_INFJUMP, TEX_PWRUP_INFHEALTH, TEX_PWRUP_AMMO, TEX_PWRUP_BEER,
    // MAKE SURE TO LIST POWER UPS BEFORE TEXTURES
    TEX_HERO, TEX_HERO2, TEX_ENEMY, TEX_BACKGROUND1, TEX_BACKGROUND2, TEX_HEALTHBAR,
    TEX_AMMOBAR, TEX_VICTORY, TEX_PROJECTILE,
    TEX_PWRUP_INFJUMP_OVERLAY, TEX_PWRUP_INFHEALTH_OVERLAY,
    TEX_PWRUP_AMMO_OVERLAY, TEX_PWRUP_BEER_OVERLAY,
    TEX_TREE1, TEX_TREE2, TEX_BENCH, TEX_NONE
};

enum TerrainTexEnum { TT_BRICK, TT_GRASS, TT_DIRT, TT_NONE };

enum FontEnum { FONT_GLOBAL };

#endif
