
#include <powerUpHandler.h>

PowerUpHandler::PowerUpHandler(std::vector < PowerUpComponent * > &componentList):
    componentList(componentList)
{
}

void PowerUpHandler::update(int dt) {
    std::vector<PowerUpComponent*>::iterator it;
    for (it = this->componentList.begin(); it != this->componentList.end(); ) {
        if (!(*it)->isValid()) {        // remove invalid components
            *it = this->componentList.back();
            this->componentList.pop_back();
        } else {
            (*it)->update(dt);
            ++it;
        }
    }
}