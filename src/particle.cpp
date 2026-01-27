#include "particle.hpp"

Particle::Particle (float posX, float posY, float velX, float velY):
    positionX {posX}, positionY {posY}, velocityX {velX}, velocityY{velY} {

}

void Particle::updatePosition (float timeInterval) {
    positionX = positionX + velocityX * timeInterval;
    positionY = positionY + velocityY * timeInterval;

}