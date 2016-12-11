#ifndef CORNERGAME_COMMAND_H
#define CORNERGAME_COMMAND_H

#include <SDL_mixer.h>
#include "consts.h"

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
class StopSoundCommand : public Command {
public:
    SfxEnum sfxType;
    StopSoundCommand(SfxEnum sfxType);
};
class LowerVolumeCommand : public Command {
public:
    LowerVolumeCommand();
};
class RaiseVolumeCommand : public Command {
public:
    RaiseVolumeCommand();
};

/* CONTROL COMMANDS */
class SwitchStateCommand : public Command {
public:
    StateEnum newState;
    SwitchStateCommand(StateEnum newState);
};

class SpawnProjCommand : public Command {
public:
    ProjEnum projType;
    float x;
    float y;
    int dir;
    int ownerID;
    float charge;
    SpawnProjCommand(ProjEnum projType);
};

class DespawnEntityCommand : public Command {
public:
    int id;
    DespawnEntityCommand(int id);
};

class TempHideCommand : public Command {
public:
    int id;
    TempHideCommand(int id);
};

class LoopLevelCommand : public Command {
public:
    LoopLevelCommand();
};

class PreviewOffCommand: public Command {
public:
    PreviewOffCommand();
};

class CameraShakeCommand: public Command {
public:
    CameraShakeCommand();
};

class TimeFreezeCommand: public Command {
public:
    int time;
    TimeFreezeCommand(int time);
};

class TimeSlowCommand: public Command {
public:
    TimeSlowCommand();
};

class TimeNormalCommand: public Command {
public:
    TimeNormalCommand();
};

class SpawnParticleCommand : public Command {
public:
    float x;
    float y;
    SpawnParticleCommand();
};

#endif
