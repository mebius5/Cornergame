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

PlaySoundCommand::PlaySoundCommand(const char* filename) {
    this->filename = filename;
}

ResetAiCommand::ResetAiCommand(Entity* entity) {
    this->entity = entity;
}
