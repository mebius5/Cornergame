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

    this->prevTime = 0;
}

SoundHandler::~SoundHandler() {
    //Cleanup Mixer
    Mix_FreeMusic(this->backgroundMusic);

    //Freeing previous chunk if exists
    if(this->sfxChunk!=NULL){
        if(Mix_Playing(this->lastChannelUsedForSFX)==0){ //If not playing
            //Mix_FreeChunk(this->sfxChunk);
            this->sfxChunk=NULL;
        } else{
            Mix_HaltChannel(this->lastChannelUsedForSFX);
            //Mix_FreeChunk(this->sfxChunk);
            this->sfxChunk=NULL;
        }
    }

    Mix_CloseAudio();
    this->backgroundMusic = NULL;
    this->sfxChunk = NULL;
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

void SoundHandler::playSFX(const char * filename, int rawtime) {
    int timeDiff = rawtime - this->prevTime;
    if (timeDiff < 150) {      // Don't play too often!
        return;
    }
    this->prevTime = rawtime;

    //Freeing previous chunk if exists
    if(this->sfxChunk!=NULL){
        if(Mix_Playing(this->lastChannelUsedForSFX)==0){ //If not playing
            //Mix_FreeChunk(this->sfxChunk);
            this->sfxChunk=NULL;
        } else{
            Mix_HaltChannel(this->lastChannelUsedForSFX);
            //Mix_FreeChunk(this->sfxChunk);
            this->sfxChunk=NULL;
        }
    }

    this->sfxChunk = Mix_LoadWAV(filename);
    if(!this->sfxChunk) {
        std::cerr << "Unable to load chunk: " << Mix_GetError() << std::endl;
    } else {
        this->lastChannelUsedForSFX=Mix_PlayChannel(-1, this->sfxChunk, 0);
        if(this->lastChannelUsedForSFX==-1) {
            std::cerr << "Mix_PlayChannel: " << Mix_GetError() << std::endl;
            // may be critical error, or maybe just no channels were free.
            // you could allocated another channel in that case...
        }
    }
}

void SoundHandler::handleSFX(std::list<Command *> & commandList, int rawtime) {
    std::list<Command *>::const_iterator it;
    for (it = commandList.begin(); it != commandList.end();) {
        Command* c = *it;
        if (PlaySoundCommand * sCmd = dynamic_cast<PlaySoundCommand *>(c)) {
            playSFX(sCmd->filename, rawtime);
            it = commandList.erase(it);
        } else {
            ++it;
        }
    }
}
