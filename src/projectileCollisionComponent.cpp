#include "collisionComponent.h"

ProjectileCollisionComponent::ProjectileCollisionComponent(Entity* entity) :
    CollisionComponent(entity, false) {
}

void ProjectileCollisionComponent::onEntityCollision(Entity* /*other*/) {
}

void ProjectileCollisionComponent::onStaticCollision(Entity* /*other*/) {
}

void ProjectileCollisionComponent::onBorderCollision() {
}
