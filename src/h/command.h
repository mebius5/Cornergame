#ifndef CORNERGAME_COMMAND_H
#define CORNERGAME_COMMAND_H

#include "entity.h"

class Entity;           // forward declared for circular dependency

class Command {
public:
    int id;
    virtual ~Command();
};

// A command to be handled by the location calculator
class LocationCommand : public Command {
public:
    Entity* entity; //the entity to move;
};

class MoveLeftCommand : public LocationCommand {
public:
    MoveLeftCommand(Entity * entity);
};

class MoveRightCommand : public LocationCommand {
public:
    MoveRightCommand(Entity * entity);
};

class MoveUpCommand : public LocationCommand {
public:
    MoveUpCommand(Entity * entity);
};

class MoveDownCommand : public LocationCommand {
public:
    MoveDownCommand(Entity * entity);
};

class SoundCommand : public Command {

};

class PlaySoundCommand : public SoundCommand {
public:
    const char* filename;
    PlaySoundCommand(const char* filename);
};

class AiCommand : public Command {
public:
    Entity* entity;
};

class ResetAiCommand : public AiCommand {
public:
    ResetAiCommand(Entity* entity);
};

#endif //CORNERGAME_COMMAND_H
