#ifndef CORNERGAME_ENUMS_H
#define CORNERGAME_ENUMS_H

// NOTE: keep NONE state the last one to make array indexing easier!
enum StateEnum { STATE_QUIT, STATE_START, STATE_PLAY, STATE_LEVEL_TRANSIT,
                 STATE_TUTORIAL,
                 STATE_MENU, STATE_HIGHSCORE, STATE_RESULTS, STATE_NONE};

enum ProjEnum { PROJ_HERO, PROJ_ENEMY };

// NOTE: if updating any of the following, MAKE SURE to update vector sizes in
// soundHander or entityBuilder for the map vectors.
enum SfxEnum { SFX_ALERT, SFX_AMMO, SFX_ARMOR, SFX_DRINK, SFX_JUMP,
               SFX_LAND, SFX_ENEMY, SFX_RUMBLE, SFX_RUNNING, SFX_SCRAPE,
               SFX_WOOSH, SFX_NONE };

enum MusicEnum { MUSIC_START, MUSIC_MENU, MUSIC_PLAY, MUSIC_HIGHSCORE };

enum TextureEnum {
    //Update array size in PowerUpComponent
    //List the powerups in order of its corresponding position in the array
    TEX_PWRUP_INFJUMP=0, TEX_PWRUP_INFHEALTH=1, TEX_PWRUP_AMMO=2,
    TEX_PWRUP_BEER=3,

    //MAKE SURE TO LIST POWER UPS BEFORE TEXTURES
    TEX_HERO, TEX_HERO2, TEX_ENEMY, TEX_BACKGROUND, TEX_HEALTHBAR,
                   TEX_AMMOBAR, TEX_VICTORY, TEX_PROJECTILE, TEX_NONE,
                    
                    TEX_PWRUP_INFJUMP_OVERLAY, TEX_PWRUP_INFHEALTH_OVERLAY,
                    TEX_PWRUP_AMMO_OVERLAY, TEX_PWRUP_BEER_OVERLAY,
                    TEX_TREE1, TEX_TREE2, TEX_BENCH

};

enum TerrainTexEnum { TT_BRICK, TT_GRASS, TT_NONE };

enum FontEnum { FONT_GLOBAL };

#endif
