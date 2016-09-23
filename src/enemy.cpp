#include "entity.h"


Enemy::Enemy(int startX, int startY, int width, int height) {
  this->location = new Location(startX, startY, width, height);
}
