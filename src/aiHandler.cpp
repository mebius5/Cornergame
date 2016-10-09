#include "aiHandler.h"

AiHandler::AiHandler(std::vector<AiComponent*>& componentList, std::vector<Entity*>& heroEntitiesList) :
        componentList(componentList),
        heroEntitiesList(heroEntitiesList){
}

void AiHandler::updateAi(int dt) {
    std::vector<AiComponent*>::iterator it;
    for (it = this->componentList.begin(); it != this->componentList.end(); ) {
        if (!(*it)->isValid()) {        // remove invalid components
            *it = this->componentList.back();
            this->componentList.pop_back();
        } else {
            std::vector<Entity*>::iterator heroInIt;
            int minDistance = 100000;
            for (heroInIt = this->heroEntitiesList.begin(); heroInIt != this->heroEntitiesList.end(); ) {
                if((*heroInIt)){
                    int distance = sqrt(((*heroInIt)->x - (*it)->entity->x ) * ((*heroInIt)->x - (*it)->entity->x) +
                                        ((*heroInIt)->y - (*it)->entity->y ) * ((*heroInIt)->y - (*it)->entity->y));

                    //If the enemy gets within 300 pixel and is the hero is the closest hero to the enemy
                    //Then we update the distance of the enemy with respect to the location of the hero
                    //Else the movement is random
                    if( distance < 300 && distance<minDistance){
                        (*it)->updateLocation(dt, (*heroInIt));
                        minDistance=distance;
                    } else{
                        (*it)->updateLocation(dt, NULL);
                    }
                    ++heroInIt;
                }
            }
            ++it;
        }
    }
}
