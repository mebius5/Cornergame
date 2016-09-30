#include "state.h"

State::State(std::list<Command*>& commandList, std::map<int, Entity*>& entityMap) :
    commandList(commandList),
    entityMap(entityMap) {
}


int State::center(int large, int small) {
    return (large / 2 - small / 2);
}

SDL_Rect State::centeredRect(int largeW, int largeH, int smallW, int smallH) {
    SDL_Rect rect = {
        center(largeW, smallW), center(largeH, smallH),
        smallW, smallH
    };
    return rect;
}
