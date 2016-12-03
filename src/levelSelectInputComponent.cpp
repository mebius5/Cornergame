#include "inputComponent.h"

LevelSelectInputComponent::LevelSelectInputComponent(Entity *entity, int index, int numOptions,
                                                     Command *nextStateCommand, bool *levelSelected):
    InputComponent(entity),
    index(index),
    numOptions(numOptions),
    currIndex(0),
    nextStateCommand(nextStateCommand),
    levelSelected(levelSelected)
{
    TextFadeInComponent* art = static_cast<TextFadeInComponent*>(entity->art);
    if (this->index==0)
        art->selectMenuItem();
}

LevelSelectInputComponent::~LevelSelectInputComponent() {
    if(this->nextStateCommand){
        delete this->nextStateCommand;
    }
    if(this->levelSelected){
        this->levelSelected = NULL;
    }
}

void LevelSelectInputComponent::updateTime(int) {
}

void LevelSelectInputComponent::keyUp(SDL_Keycode) {

}

void LevelSelectInputComponent::keyDown(SDL_Keycode keycode) {
    TextFadeInComponent* art = static_cast<TextFadeInComponent*>(this->entity->art);

    // Check if up arrow or down arrow was pressed
    switch (keycode) {
        case SDLK_UP:
            this->currIndex--;
            if (this->currIndex < 0)
                this->currIndex = this->numOptions - 1;
            break;
        case SDLK_DOWN:
            this->currIndex++;
            if (this->currIndex == numOptions)
                this->currIndex = 0;
            break;
        case SDLK_SPACE:
            if(levelSelected[this->index] && this->currIndex == this->index){
                art->deselectMenuItem();
                if(this->currIndex < MAXLEVELS){
                    levelSelected[this->currIndex]=false;
                }
            } else if (!levelSelected[this->index] && this->currIndex == this->index){
                art->selectMenuItem();
                if(this->currIndex < MAXLEVELS){
                    levelSelected[this->currIndex]=true;
                }
            }
            if (this->nextStateCommand && this->currIndex == MAXLEVELS){ //Play button
                art->deselectMenuItem();

                bool thereIsALevelSelected=false;

                for(int i = 0; i<MAXLEVELS;i++){ //Checks to see if there's a level selected
                    if(levelSelected[i]){
                        thereIsALevelSelected=true;
                    }
                }

                if(thereIsALevelSelected){
                    Component::commandList->push_back(this->nextStateCommand);
                    return;
                }
            }
            break;
        default:
            return;
    }

    if (this->currIndex != this->index) {
        if(levelSelected[this->index]==false){
            art->deselectMenuItem();
        }
    } else if (this->currIndex == this->index) {
        art->selectMenuItem();
    }
    return;
}