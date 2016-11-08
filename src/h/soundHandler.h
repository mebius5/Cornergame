#ifndef CORNERGAME_SOUND_HANDLER_H
#define CORNERGAME_SOUND_HANDLER_H

#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include "command.h"
#include "enums.h"

class SoundHandler {
private:
    static const int NCHANS = 20;
    std::vector<Command*>& commandList;
    std::vector<Mix_Chunk*> sfxMap;
    std::vector<Mix_Music*> musicMap;
    std::vector<int> timeElapsed;        // time passed since a sound was played
    void playSfx(SfxEnum sfxType);
    void stopSfx(int channel);           // note that channel number = sfxType
public:
    SoundHandler(std::vector<Command*>& commandList);
    ~SoundHandler();
    void loadMusic(const char* filename, MusicEnum musicType);
    void loadSfx(const char* filename, SfxEnum sfxType);
    void freeMusic();
    void freeSfx();
    void playBackgroundMusic(MusicEnum musicType);
    void stopBackgroundMusic();
    void stopAllSfx();
    void handleSfx(int dt);
};

#endif
