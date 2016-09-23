#include "entity.h"


Enemy::Enemy(int startX, int startY, SDL_Texture* texture) {
  this->location = new Location(startX, startY);
}
