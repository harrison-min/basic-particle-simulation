#pragma once
#include <vector>
#include "gravity.hpp"

class Particle {
    public:
        float positionX;
        float positionY;
        Particle (float posX, float posY, float velX, float velY, float startingMass);
        float velocityX;
        float velocityY;
        uint32_t color;
    private:
        float mass;
};


struct ParticlePositionUpdater {
    float timeInterval;
    Particle * particles;

    __device__ void operator() (int index) {
        particles[index].positionX = particles[index].velocityX * timeInterval + particles[index].positionX;
        particles[index].positionY = particles[index].velocityY * timeInterval + particles[index].positionY;
    }
};

struct ParticleVelocityUpdater {
    float timeInterval;
    Particle * particles;
    float * accelX;
    float * accelY;
    int totalWidth;
    int totalHeight;

    __device__ void operator() (int index) {
        int gridX = static_cast<int>(particles[index].positionX);
        int gridY = static_cast<int>(particles[index].positionY);

        if (gridX < 0 || gridY < 0 || gridX > totalWidth || gridY > totalHeight) {
            return;
        }

        int gridIndex = gridX + gridY * totalWidth;
        particles[index].velocityX = accelX[gridIndex] * timeInterval + particles[index].velocityX;
        particles[index].velocityY = accelY[gridIndex] * timeInterval + particles[index].velocityY;
        
        float absoluteVelocitySquared = (particles[index].velocityX * particles[index].velocityX) +
            (particles[index].velocityY * particles[index].velocityY);
        float normalizedVelocity = -500 /(absoluteVelocitySquared + 500) + 1;
        uint8_t red = static_cast<uint8_t> (normalizedVelocity * normalizedVelocity* normalizedVelocity * 255);
        uint8_t green = static_cast<uint8_t> ((-8 * (normalizedVelocity-.5) * (normalizedVelocity-.5) + 1)  * 255);
        uint8_t blue = static_cast<uint8_t> (1/( 8* normalizedVelocity + 1) * 200 + 55);

        particles[index].color = (0xFF << 24) | (red << 16) | (green << 8) | blue;


    }
};
