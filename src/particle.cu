#include "particle.hpp"

Particle::Particle (float posX, float posY, float velX, float velY, float startingMass):
    positionX {posX}, positionY {posY}, velocityX {velX}, velocityY{velY}, mass{startingMass}{

}

void Particle::updatePosition (float timeInterval) {
    positionX = positionX + velocityX * timeInterval;
    positionY = positionY + velocityY * timeInterval;

}
        

void Particle::updateVelocity (float timeInterval, GravityField& gravity) {
    int index = static_cast<int>(positionX) + static_cast<int>(positionY) * gravity.totalWidth;
    if (index >= (gravity.totalHeight * gravity.totalWidth) || index < 0) {
        return;
    }
    velocityX = velocityX + gravity.accelerationFieldXcomponent[index] * timeInterval;
    velocityY = velocityY + gravity.accelerationFieldYcomponent[index] * timeInterval;
}