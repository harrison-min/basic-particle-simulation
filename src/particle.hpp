#pragma once
#include <vector>


class Particle {
    private:
        float velocityX;
        float velocityY;
    public:
        float positionX;
        float positionY;
        Particle (float posX, float posY, float velX, float velY);
        void updatePosition (float timeInterval);
};