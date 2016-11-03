#include "command.h"

PlaySoundCommand::PlaySoundCommand(SfxEnum sfxType) :
    sfxType(sfxType) {
}

SwitchStateCommand::SwitchStateCommand(StateEnum newState) :
    newState(newState) {
}

SpawnProjCommand::SpawnProjCommand(ProjEnum projType) :
    projType(projType) {
}

DespawnEntityCommand::DespawnEntityCommand(int id) :
    id(id) {
}

RespawnPowerUpsCommand::RespawnPowerUpsCommand() {
}

PreviewOffCommand::PreviewOffCommand() {

}

CameraShakeCommand::CameraShakeCommand() {
}
