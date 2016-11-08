#include "soundHandler.h"

SoundHandler::SoundHandler(std::vector<Command*>& cmdList) :
    commandList(cmdList),
    sfxMap(20),             // initialized to 5 positions. Expand if needed!
    musicMap(5),
    timeElapsed(150),
    lastChannelUsedForSfx(0) {
        Mix_VolumeMusic(MIX_MAX_VOLUME / 10);
        Mix_AllocateChannels(20);
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
    Mix_FadeInMusic(this->musicMap[music], -1, 3000);
}

void SoundHandler::stopBackgroundMusic() {
    Mix_HaltMusic();
}

void SoundHandler::playSfx(SfxEnum sfxType) {
    if (this->timeElapsed < 150)      // Don't play too often!
        return;     //TODO: FIX THIS
    this->timeElapsed = 0;

    int channel = this->stopSfx(sfxType);
    int num_loops = 0;
    if (sfxType == SFX_RUNNING || sfxType == SFX_SCRAPE)
        num_loops = -1;
    this->lastChannelUsedForSfx = Mix_PlayChannel(channel, this->sfxMap[sfxType], num_loops);
    if (this->lastChannelUsedForSfx == -1) {
        std::cerr << "Mix_PlayChannel: " << Mix_GetError() << std::endl;
        // may be critical error, or maybe just no channels were free.
        // you could allocated another channel in that case...
    }
}

int SoundHandler::stopSfx(SfxEnum sfxType) {
    int channel = (int) sfxType;
    if (Mix_Playing(channel))
        Mix_HaltChannel(channel);
    return channel;
}

void SoundHandler::handleSfx(int dt) {
    this->timeElapsed += dt;
    std::vector<Command*>::iterator it;
    for (it = this->commandList.begin(); it != this->commandList.end(); ) {
        if (PlaySoundCommand* sCmd = dynamic_cast<PlaySoundCommand*>(*it)) {
            this->playSfx(sCmd->sfxType);
            *it = this->commandList.back();
            this->commandList.pop_back();
        } else if (StopSoundCommand* sCmd = dynamic_cast<StopSoundCommand*>(*it)) {
            this->stopSfx(sCmd->sfxType);
            *it = this->commandList.back();
            this->commandList.pop_back();
        } else {
            ++it;
        }
    }
}
