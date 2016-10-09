#include "aiHandler.h"

AiHandler::AiHandler(std::vector<AiComponent*>& componentList, std::vector<InputComponent*>& inputComponentList) :
    componentList(componentList),
    inputComponentList(inputComponentList){
}

void AiHandler::updateAi(int dt) {
    std::vector<AiComponent*>::iterator it;
    for (it = this->componentList.begin(); it != this->componentList.end(); ) {
        if (!(*it)->isValid()) {        // remove invalid components
            *it = this->componentList.back();
            this->componentList.pop_back();
        } else {
            std::vector<InputComponent*>::iterator heroInIt;
            int minDistance = 100000;
            for (heroInIt = this->inputComponentList.begin(); heroInIt != this->inputComponentList.end(); ) {
                if (!(*heroInIt)->isValid()) {        // remove invalid components
                    *heroInIt = this->inputComponentList.back();
                    this->inputComponentList.pop_back();
                } else {
                    if(dynamic_cast<HeroInputComponent*>((*heroInIt))){
                        (*heroInIt)->updateLocation(dt);
                        int distance = sqrt(((*heroInIt)->entity->x - (*it)->entity->x ) * ((*heroInIt)->entity->x - (*it)->entity->x) +
                                            ((*heroInIt)->entity->y - (*it)->entity->y ) * ((*heroInIt)->entity->y - (*it)->entity->y));

                        //If the enemy gets within 300 pixel and is the hero is the closest hero to the enemy
                        //Then we update the distance of the enemy with respect to the location of the hero
                        //Else the movement is random
                        if( distance < 300 && distance<minDistance){
                            (*it)->updateLocation(dt, (*heroInIt)->entity);
                            minDistance=distance;
                        } else{
                            (*it)->updateLocation(dt, NULL);
                        }
                        ++heroInIt;
                    }
                }
            }

            //(*it)->updateLocation(dt);
            ++it;
        }
    }
}
