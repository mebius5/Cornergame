#include "state.h"

State::State(EntityManager& entityManager, std::vector<Command*>& cmdList,
             SDL_Renderer* renderer, int windowW, int windowH,
             std::vector<Entity*>& savedEntities) :
    windowW(windowW),
    windowH(windowH),
    entityManager(entityManager),
    commandList(cmdList),
    renderer(renderer),
    savedEntities(savedEntities) {
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
