#include "soundHandler.h"

SoundHandler::SoundHandler() {
    // Initialize Mixer
    if (Mix_Init(MIX_INIT_MOD)) {
        std::cerr << "The mixer failed to initialize!" << std::endl;
        return;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        std::cerr << "The mixer failed to initialize!" << std::endl;
        return;
    }
}

SoundHandler::~SoundHandler() {
    //Cleanup Mixer
    Mix_FreeMusic(this->backgroundMusic);
    Mix_CloseAudio();
    this->backgroundMusic = NULL;
}

Mix_Music * SoundHandler::loadMusic( const char * filename) {
    //Load backgroundMusic
    Mix_Music * music = Mix_LoadMUS(filename);
    if (!this->backgroundMusic) {
        std::cerr << "Unable to load music: " << SDL_GetError() << std::endl;
    }
    return music;
}

void SoundHandler::playBackgroundMusic(const char *filename) {
    this->backgroundMusic = loadMusic(filename);
    Mix_PlayMusic(this->backgroundMusic, -1);
}

void SoundHandler::playSFX(const char * filename) {
    Mix_Chunk * music = Mix_LoadWAV(filename);
    if(!music) {
        std::cerr << "Unable to load chunk: " << Mix_GetError() << std::endl;
    } else {
        if(Mix_PlayChannel(-1, music, -1)==-1) {
            std::cerr << "Mix_PlayChannel: " << Mix_GetError() << std::endl;
            // may be critical error, or maybe just no channels were free.
            // you could allocated another channel in that case...
        }
    }
}