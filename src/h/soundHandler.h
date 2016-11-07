#ifndef CORNERGAME_SOUND_HANDLER_H
#define CORNERGAME_SOUND_HANDLER_H

#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include "command.h"
#include "enums.h"

class SoundHandler {
private:
    std::vector<Command*>& commandList;
    std::vector<Mix_Chunk*> sfxMap;
    std::vector<Mix_Music*> musicMap;
    int timeElapsed;               // time passed since a sound was played
    int lastChannelUsedForSfx;
    void playSfx(SfxEnum sfxType);
    int stopSfx(SfxEnum sfxType);
public:
    SoundHandler(std::vector<Command*>& commandList);
    ~SoundHandler();
    void loadMusic(const char* filename, MusicEnum musicType);
    void loadSfx(const char* filename, SfxEnum sfxType);
    void freeMusic();
    void freeSfx();
    void playBackgroundMusic(MusicEnum musicType);
    void stopBackgroundMusic();
    void handleSfx(int dt);
};

#endif
