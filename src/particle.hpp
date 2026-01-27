#pragma once
#include <vector>
#include "gravity.hpp"

class Particle {
    public:
        float positionX;
        float positionY;
        Particle (float posX, float posY, float velX, float velY, float startingMass);
        void updateVelocity (float timeInterval, GravityField& gravity);
        void updatePosition (float timeInterval);
    private:
        float velocityX;
        float velocityY;
        float mass;
};