#ifndef CORNERGAME_COMMAND_H
#define CORNERGAME_COMMAND_H

#include <SDL_mixer.h>
#include "enums.h"

class Command {
public:
    virtual ~Command() { };
};

/* SOUND COMMANDS */
class PlaySoundCommand : public Command {
public:
    SfxEnum sfxType;
    PlaySoundCommand(SfxEnum sfxType);
};

/* CONTROL COMMANDS */
class SwitchStateCommand : public Command {
public:
    StateEnum newState;
    SwitchStateCommand(StateEnum newState);
};

class SpawnEntityCommand : public Command {
public:
    ProjEnum projType;
    int x;
    int y;
    int dir;
    int ownerID;
    SpawnEntityCommand(ProjEnum projType);
};

class DespawnEntityCommand : public Command {
public:
    int id;
    DespawnEntityCommand(int id);
};

#endif
