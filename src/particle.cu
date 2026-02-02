#include "particle.hpp"

Particle::Particle (float posX, float posY, float posZ, float velX, float velY, float velZ, float startingRadius, float startingMass):
    positionX {posX}, positionY {posY}, positionZ {posZ}, 
    velocityX {velX}, velocityY{velY}, velocityZ{velZ}, 
    radius {startingRadius},
    mass{startingMass},
    color{0xFFFFFFFF}{

}
