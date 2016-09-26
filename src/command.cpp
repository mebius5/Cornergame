#include "command.h"

Command::~Command() {

}

LocationCommand::LocationCommand(Entity* entity) :
        entity(entity) {
}

MoveUpCommand::MoveUpCommand(Entity* entity) :
        LocationCommand(entity) {
}

MoveDownCommand::MoveDownCommand(Entity* entity) :
        LocationCommand(entity) {
}

MoveLeftCommand::MoveLeftCommand(Entity* entity) :
        LocationCommand(entity) {
}

MoveRightCommand::MoveRightCommand(Entity* entity) :
        LocationCommand(entity) {
}

PlaySoundCommand::PlaySoundCommand(Mix_Chunk* sfxChunk) :
        sfxChunk(sfxChunk) {
}

PlaySoundCommand::~PlaySoundCommand() {
    Mix_FreeChunk(this->sfxChunk);
    this->sfxChunk = NULL;
}

AiCommand::AiCommand(Entity* entity) :
        entity(entity) {
}

ResetAiCommand::ResetAiCommand(Entity* entity) :
        AiCommand(entity) {
}
