#include "soundHandler.h"

SoundHandler::SoundHandler(std::list<Command*>& cmdList) :
        commandList(cmdList),
        prevTime(0) {
}

SoundHandler::~SoundHandler() {
    if (this->backgroundMusic)
        Mix_FreeMusic(this->backgroundMusic);
    this->backgroundMusic = NULL;

    if (Mix_Playing(this->lastChannelUsedForSFX))
        Mix_HaltChannel(this->lastChannelUsedForSFX);
}

Mix_Music* SoundHandler::loadMusic(const char* filename) {
    //Load backgroundMusic
    Mix_Music* music = Mix_LoadMUS(filename);
    if (!music) {
        std::cerr << "Unable to load music: " << SDL_GetError() << std::endl;
    }
    return music;
}

void SoundHandler::playBackgroundMusic(const char* filename) {
    this->backgroundMusic = loadMusic(filename);
    Mix_PlayMusic(this->backgroundMusic, -1);
}

void SoundHandler::playSFX(Mix_Chunk* sfxChunk, int rawtime) {
    int timeDiff = rawtime - this->prevTime;
    if (timeDiff < 150) {      // Don't play too often!
        return;
    }
    this->prevTime = rawtime;

    if (Mix_Playing(this->lastChannelUsedForSFX))
        Mix_HaltChannel(this->lastChannelUsedForSFX);

    this->lastChannelUsedForSFX=Mix_PlayChannel(-1, sfxChunk, 0);
    if(this->lastChannelUsedForSFX==-1) {
        std::cerr << "Mix_PlayChannel: " << Mix_GetError() << std::endl;
        // may be critical error, or maybe just no channels were free.
        // you could allocated another channel in that case...
    }
}

void SoundHandler::handleSFX(int rawtime) {
    std::list<Command *>::const_iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end();) {
        Command* c = *it;
        if (PlaySoundCommand* sCmd = dynamic_cast<PlaySoundCommand*>(c)) {
            playSFX(sCmd->sfxChunk, rawtime);
            it = this->commandList.erase(it);
        } else {
            ++it;
        }
    }
}
