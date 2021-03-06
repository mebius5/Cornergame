#include "aiComponent.h"
#include "artComponent.h"
#include "collisionComponent.h"
#include "inputComponent.h"
#include "powerUpComponent.h"

#include "component.h"


std::vector<Command*>* Component::commandList = NULL;

Component::Component(Entity* entity) :
    valid(true),
    entity(entity) {
}

void Component::validate() {
    this->valid = true;
}

void Component::invalidate() {
    this->valid = false;
}

bool Component::isValid() {
    return this->valid;
}

void Component::setCommandList(std::vector<Command*>* commandListPtr) {
    Component::commandList = commandListPtr;
}

AiComponent::AiComponent(Entity* entity) :
    Component(entity) {
}

ArtComponent::ArtComponent(Entity* entity, LayerEnum layer, bool movesWithCamera) :
        Component(entity),
    lightTexture(NULL),
    layer(layer),
    movesWithCamera(movesWithCamera),
    isVisible(true),
    globalLighting(false)
{
    if (this->movesWithCamera) {
        this->offsetX = (int) entity->x;
        this->offsetY = (int) entity->y;
    }
}

Texture * ArtComponent::getLightTexture() {
    return this->lightTexture;
}


void ArtComponent::setLightTexture(Texture *lightTexture, bool addTrueModFalse) {
    this->lightTexture = lightTexture;
    if(addTrueModFalse){
        globalLighting=false;
        SDL_SetTextureBlendMode(lightTexture->sdlTexture, SDL_BLENDMODE_ADD);
    } else {
        globalLighting=true;
        SDL_SetTextureBlendMode(lightTexture->sdlTexture, SDL_BLENDMODE_MOD);
    }
}

CollisionComponent::CollisionComponent(Entity* entity) :
    Component(entity) {
}

int CollisionComponent::sign(float x) {
    if (x < 0) {
        return -1;
    } else {
        return 1;
    }
}


StaticCollisionComponent::StaticCollisionComponent(Entity* entity) :
    CollisionComponent(entity) {
    //xBinIndex(0),       //TODO: init this index and use it?
    //yBinIndex(0) {
}

DynamicCollisionComponent::DynamicCollisionComponent(Entity* entity) :
    CollisionComponent(entity),
    onGround(false),
    onLeftWall(false),
    onRightWall(false) {
}

InputComponent::InputComponent(Entity* entity) :
    Component(entity) {
}
