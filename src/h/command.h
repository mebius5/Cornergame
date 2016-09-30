#ifndef CORNERGAME_COMMAND_H
#define CORNERGAME_COMMAND_H

#include <SDL_mixer.h>
#include "entity.h"

class Entity;           // forward declared for circular dependency

class Command {
public:
    int id;
    virtual ~Command();
};

class SoundCommand : public Command {

};

class PlaySoundCommand : public SoundCommand {
public:
    Mix_Chunk* sfxChunk;
    PlaySoundCommand(Mix_Chunk* sfxChunk);
    ~PlaySoundCommand();
};

class InputCommand : public Command {
public:
    Entity* entity;
};

class ResetAiCommand : public InputCommand {
public:
    ResetAiCommand(Entity* entity);
};

#endif
