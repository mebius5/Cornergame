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

TempHideCommand::TempHideCommand(int id) :
    id(id) {
}

LoopLevelCommand::LoopLevelCommand() {
}

PreviewOffCommand::PreviewOffCommand() {

}

CameraShakeCommand::CameraShakeCommand() {
}
