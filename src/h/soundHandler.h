#ifndef CORNERGAME_SOUND_HANDLER_H
#define CORNERGAME_SOUND_HANDLER_H

#include <SDL_mixer.h>
#include <iostream>
#include <list>
#include "command.h"


class SoundHandler {
private:
    Mix_Music * backgroundMusic;
    Mix_Chunk * sfxChunk;
    Mix_Music * loadMusic(const char * filename);
    void playSFX(const char * filename);
public:
    SoundHandler();
    ~SoundHandler();
    void playBackgroundMusic(const char * filename);
    void handleSFX(std::list<Command *> & commandList);
};

#endif //CORNERGAME_SOUND_HANDLER_H
