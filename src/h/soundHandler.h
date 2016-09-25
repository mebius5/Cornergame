#ifndef CORNERGAME_SOUND_HANDLER_H
#define CORNERGAME_SOUND_HANDLER_H

#include <SDL_mixer.h>
#include <iostream>


class SoundHandler {
private:
    Mix_Music * backgroundMusic;
    Mix_Music * loadMusic(const char * filename);
public:
    SoundHandler();
    ~SoundHandler();
    void playBackgroundMusic(const char * filename);
    void playSFX(const char * filename);
};

#endif //CORNERGAME_SOUND_HANDLER_H
