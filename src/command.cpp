#include "command.h"

Command::~Command() {

}

PlaySoundCommand::PlaySoundCommand(Mix_Chunk* sfxChunk) :
    sfxChunk(sfxChunk) {
}

PlaySoundCommand::~PlaySoundCommand() {
    if(this->sfxChunk){
        Mix_FreeChunk(this->sfxChunk);
        this->sfxChunk = NULL;
    }
}

SwitchStateCommand::SwitchStateCommand(StateEnum newState) :
    newState(newState) {
}
