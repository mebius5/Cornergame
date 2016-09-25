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
    Mix_FreeMusic(this->music);
    Mix_CloseAudio();
    this->music = NULL;
}

void SoundHandler::loadMusic(const char * filename) {
    //Load music
    this->music = Mix_LoadMUS(filename);
    if (!this->music) {
        std::cerr << "Unable to load music: " << SDL_GetError() << std::endl;
    }
}

void SoundHandler::playBackgroundMusic(const char *filename) {
    loadMusic(filename);
    Mix_PlayMusic(this->music, -1);
}
