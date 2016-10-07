#include "command.h"

PlaySoundCommand::PlaySoundCommand(SfxEnum sfxType) :
    sfxType(sfxType) {
}

SwitchStateCommand::SwitchStateCommand(StateEnum newState) :
    newState(newState) {
}
