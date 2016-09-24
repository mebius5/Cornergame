#include "inputHandler.h"

InputHandler::InputHandler(std::map<int, Entity *> & entityMap,
                           std::list<Command *> & commandList):
        entityMap(entityMap), commandList(commandList) {
}

void InputHandler::handleKeyDown(SDL_Event event) {

    std::map<int, Entity*>::const_iterator it;
    for (it = entityMap.begin(); it != entityMap.end(); ++it) {
        if(it ->second->input){
            std::map<SDL_Keycode, Command * > & onKeyDownMap = it ->second->input->onKeyDownMap;
            try{
                commandList.push_back(onKeyDownMap.at(event.key.keysym.sym));
            } catch (const std::out_of_range & oor){

            }
        }
    }
}