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

class SpawnProjCommand : public Command {
public:
    ProjEnum projType;
    int x;
    int y;
    int dir;
    int ownerID;
    float charge;
    SpawnProjCommand(ProjEnum projType);
};

class SpawnPwrupOverlay : public Command {
public:
    TextureEnum pwrtype;
    int x;
    int y;
    int ownerID;
    SpawnPwrupOverlay(TextureEnum pwrtype);
};

class DespawnEntityCommand : public Command {
public:
    int id;
    DespawnEntityCommand(int id);
};

class RespawnPowerUpsCommand : public Command {
public:
    RespawnPowerUpsCommand();
};

class PreviewOffCommand: public Command {
public:
    PreviewOffCommand();
};

class CameraShakeCommand: public Command {
public:
    CameraShakeCommand();
};

#endif
