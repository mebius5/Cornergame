#include "command.h"

Command::~Command() {

}

PlaySoundCommand::PlaySoundCommand(Mix_Chunk* sfxChunk) :
        sfxChunk(sfxChunk) {
}

PlaySoundCommand::~PlaySoundCommand() {
    Mix_FreeChunk(this->sfxChunk);
    this->sfxChunk = NULL;
}

ResetAiCommand::ResetAiCommand(Entity* entity) {
    this->entity = entity;
}
