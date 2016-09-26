#include "command.h"

Command::~Command() {

}

MoveUpCommand::MoveUpCommand(Entity* entity) {
    this->entity = entity;
}

MoveDownCommand::MoveDownCommand(Entity* entity) {
    this->entity = entity;
}

MoveLeftCommand::MoveLeftCommand(Entity* entity) {
    this->entity = entity;
}

MoveRightCommand::MoveRightCommand(Entity* entity) {
    this->entity = entity;
}

PlaySoundCommand::PlaySoundCommand(Mix_Chunk* sfxChunk) {
    this->sfxChunk = sfxChunk;
}

PlaySoundCommand::~PlaySoundCommand() {
    Mix_FreeChunk(this->sfxChunk);
    this->sfxChunk = NULL;
}

ResetAiCommand::ResetAiCommand(Entity* entity) {
    this->entity = entity;
}
