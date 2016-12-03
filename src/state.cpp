#include "state.h"

State::State(EntityManager& entityManager, std::vector<Command*>& cmdList,
             SDL_Renderer* renderer, int windowW, int windowH) :
    windowW(windowW),
    windowH(windowH),
    entityManager(entityManager),
    commandList(cmdList),
    renderer(renderer) {
}