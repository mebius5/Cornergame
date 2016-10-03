#include "state.h"

State::State(std::list<Command*>& cmdList, std::map<int, Entity*>& entityMap,
             SDL_Renderer* renderer, int windowW, int windowH) :
        windowW(windowW),
        windowH(windowH),
        commandList(cmdList),
        entityMap(entityMap),
        renderer(renderer) {
}

int State::center(int large, int small) {
    return (large / 2 - small / 2);
}

SDL_Rect State::centeredRect(int largeW, int largeH, int smallW, int smallH) {
    SDL_Rect rect = {
            State::center(largeW, smallW), State::center(largeH, smallH),
            smallW, smallH
    };
    return rect;
}
