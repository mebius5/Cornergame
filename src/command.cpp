#include "command.h"

PlaySoundCommand::PlaySoundCommand(SfxEnum sfxType) :
    sfxType(sfxType) {
}

SwitchStateCommand::SwitchStateCommand(StateEnum newState) :
    newState(newState) {
}

SpawnEntityCommand::SpawnEntityCommand(ProjEnum projType) :
    projType(projType) {
}

DespawnEntityCommand::DespawnEntityCommand(int id) :
    id(id) {
}
