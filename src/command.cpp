#include "command.h"

PlaySoundCommand::PlaySoundCommand(SfxEnum sfxType) :
    sfxType(sfxType) {
}

StopSoundCommand::StopSoundCommand(SfxEnum sfxType) :
    sfxType(sfxType) {
}

LowerVolumeCommand::LowerVolumeCommand() {
}

RaiseVolumeCommand::RaiseVolumeCommand() {
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

TimeFreezeCommand::TimeFreezeCommand(int time) :
    time(time) {
}

TimeSlowCommand::TimeSlowCommand() {
}

TimeNormalCommand::TimeNormalCommand() {
}

SpawnParticleCommand::SpawnParticleCommand() {
}
