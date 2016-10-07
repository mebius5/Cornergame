#include "soundHandler.h"

SoundHandler::SoundHandler(std::list<Command*>& cmdList) :
    commandList(cmdList),
    sfxMap(5),             // initialized to 5 positions. Expand if needed!
    musicMap(5),
    timeElapsed(150),
    lastChannelUsedForSfx(0) {
}

SoundHandler::~SoundHandler() {
    if (Mix_Playing(this->lastChannelUsedForSfx))
        Mix_HaltChannel(this->lastChannelUsedForSfx);
    this->stopBackgroundMusic();
    this->freeMusic();
    this->freeSfx();
}

void SoundHandler::loadMusic(const char* filename, MusicEnum musicType) {
    Mix_Music* music = Mix_LoadMUS(filename);
    if (!music)
        std::cerr << "Unable to load music: " << SDL_GetError() << std::endl;
    this->musicMap[musicType] = music;
}

void SoundHandler::loadSfx(const char* filename, SfxEnum sfxType) {
    Mix_Chunk* chunk = Mix_LoadWAV(filename);
    if (!chunk)
        std::cerr << "Failed to load chunk: " << Mix_GetError() << std::endl;
    this->sfxMap[sfxType] = chunk;
}

void SoundHandler::freeMusic() {
    std::vector<Mix_Music*>::const_iterator it;
    for (it = this->musicMap.begin(); it != this->musicMap.end(); ++it) {
        if (*it)
            Mix_FreeMusic(*it);
    }
    this->musicMap.clear();
}

void SoundHandler::freeSfx() {
    std::vector<Mix_Chunk*>::const_iterator it;
    for (it = this->sfxMap.begin(); it != this->sfxMap.end(); ++it) {
        if (*it)
            Mix_FreeChunk(*it);
    }
    this->sfxMap.clear();
}

void SoundHandler::playBackgroundMusic(MusicEnum music) {
    Mix_PlayMusic(this->musicMap[music], -1);
}

void SoundHandler::stopBackgroundMusic() {
    Mix_HaltMusic();
}

void SoundHandler::playSfx(SfxEnum sfxType) {
    if (this->timeElapsed < 150)      // Don't play too often!
        return;
    this->timeElapsed = 0;

    if (Mix_Playing(this->lastChannelUsedForSfx))
        Mix_HaltChannel(this->lastChannelUsedForSfx);

    this->lastChannelUsedForSfx = Mix_PlayChannel(-1, this->sfxMap[sfxType], 0);
    if (this->lastChannelUsedForSfx == -1) {
        std::cerr << "Mix_PlayChannel: " << Mix_GetError() << std::endl;
        // may be critical error, or maybe just no channels were free.
        // you could allocated another channel in that case...
    }
}

void SoundHandler::handleSfx(int dt) {
    this->timeElapsed += dt;
    std::list<Command*>::const_iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end(); ) {
        Command* c = *it;
        if (PlaySoundCommand* sCmd = dynamic_cast<PlaySoundCommand*>(c)) {
            this->playSfx(sCmd->sfxType);
            it = this->commandList.erase(it);
        } else {
            ++it;
        }
    }
}
