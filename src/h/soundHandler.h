#ifndef CORNERGAME_SOUND_HANDLER_H
#define CORNERGAME_SOUND_HANDLER_H

#include <SDL_mixer.h>
#include <iostream>
#include <list>
#include "command.h"

class SoundHandler {
private:
    std::list<Command*>& commandList;
    int timeElapsed;               // time passed since a sound was played
    Mix_Music* backgroundMusic;
    int lastChannelUsedForSFX;
    Mix_Music* loadMusic(const char* filename);
    void playSFX(Mix_Chunk* sfxChunk);
public:
    SoundHandler(std::list<Command*>& commandList);
    ~SoundHandler();
    void playBackgroundMusic(const char* filename);
    void stopBackgroundMusic();
    void handleSFX(int dt);
};

#endif
