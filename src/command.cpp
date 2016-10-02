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

SwitchStateCommand::SwitchStateCommand(int newState) :
    newState(newState) {
}

SelectMenuOptionCommand::SelectMenuOptionCommand(Entity* entity) {
    this->entity = entity;
}

DeselectMenuOptionCommand::DeselectMenuOptionCommand(Entity* entity) {
    this->entity = entity;
}
