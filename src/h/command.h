#ifndef CORNERGAME_COMMAND_H
#define CORNERGAME_COMMAND_H

#include <SDL_mixer.h>
#include "enums.h"

class Command {
public:
    int id;
    virtual ~Command();
};

/* SOUND COMMANDS */
class SoundCommand : public Command { };

class PlaySoundCommand : public SoundCommand {
public:
    Mix_Chunk* sfxChunk;
    PlaySoundCommand(Mix_Chunk* sfxChunk);
    ~PlaySoundCommand();
};

/* INPUT COMMANDS */
class InputCommand : public Command { };
class ResetAiCommand : public InputCommand { };

/* ART COMMANDS */
class ArtCommand : public Command { };
class SelectMenuOptionCommand : public ArtCommand { };
class DeselectMenuOptionCommand : public ArtCommand { };

/* CONTROL COMMANDS */
class ControlCommand : public Command { };

class SwitchStateCommand : public ControlCommand {
public:
    StateEnum newState;
    SwitchStateCommand(StateEnum newState);
};

#endif
