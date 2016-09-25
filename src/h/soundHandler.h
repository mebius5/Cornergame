#ifndef CORNERGAME_SOUND_HANDLER_H
#define CORNERGAME_SOUND_HANDLER_H

#include <SDL_mixer.h>
#include <iostream>
#include <list>
#include "command.h"

class SoundHandler {
private:
    int prevTime;                 // last time a sound was played
    Mix_Music * backgroundMusic;
    Mix_Chunk * sfxChunk;
    int lastChannelUsedForSFX;
    Mix_Music * loadMusic(const char * filename);
    void playSFX(const char * filename, int rawtime);
public:
    SoundHandler();
    ~SoundHandler();
    void playBackgroundMusic(const char * filename);
    void handleSFX(std::list<Command *> & commandList, int rawtime);
};

#endif //CORNERGAME_SOUND_HANDLER_H
