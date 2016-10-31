#ifndef CORNERGAME_ENUMS_H
#define CORNERGAME_ENUMS_H

// NOTE: keep NONE state the last one to make array indexing easier!
enum StateEnum { STATE_QUIT, STATE_START, STATE_PLAY, STATE_LEVEL_TRANSIT,
                 STATE_MENU, STATE_HIGHSCORE, STATE_RESULTS, STATE_NONE};

enum ProjEnum { PROJ_HERO, PROJ_ENEMY };

// NOTE: if updating any of the following, MAKE SURE to update vector sizes in
// soundHander or entityBuilder for the map vectors.
enum SfxEnum { SFX_ALERT, SFX_NONE };

enum MusicEnum { MUSIC_START, MUSIC_MENU, MUSIC_PLAY, MUSIC_HIGHSCORE };

enum TextureEnum { TEX_HERO, TEX_HERO2, TEX_ENEMY, TEX_BACKGROUND, TEX_HEALTHBAR,
                   TEX_AMMOBAR, TEX_VICTORY, TEX_PROJECTILE, TEX_NONE,
                    TEX_PWRUP_INFJUMP, TEX_PWRUP_INFHEALTH,
                    TEX_TREE1, TEX_TREE2, TEX_BENCH};

enum TerrainTexEnum { TT_BRICK, TT_GRASS, TT_NONE };

enum FontEnum { FONT_GLOBAL };

#endif
