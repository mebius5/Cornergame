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

ResetAiCommand::ResetAiCommand(Entity* entity) {
    this->entity = entity;
}

SwitchStateCommand::SwitchStateCommand(StateEnum newState) :
    newState(newState) {
}

SelectMenuOptionCommand::SelectMenuOptionCommand(Entity* entity) {
    this->entity = entity;
}

DeselectMenuOptionCommand::DeselectMenuOptionCommand(Entity* entity) {
    this->entity = entity;
}
