#pragma once
#include <vector>
#include "gravity.hpp"

class Particle {
    public:
        Particle (float posX, float posY, float posZ, float velX, float velY, float velZ, float startingRadius, float startingMass);
        float positionX;
        float positionY;
        float positionZ;
        float velocityX;
        float velocityY;
        float velocityZ;
        float radius;
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
        particles[index].positionZ = particles[index].velocityZ * timeInterval + particles[index].positionZ;
    }
};

struct ParticleVelocityUpdater {
    float timeInterval;
    Particle * particles;
    GravityWell * wells;
    int totalWidth;
    int totalHeight;
    int totalDepth;
    size_t numberOfWells;

    __device__ void operator() (int index) {
        Particle& currentParticle = particles[index];

        float accelX = 0;
        float accelY = 0;
        float accelZ = 0;

        for (size_t i = 0; i < numberOfWells; i ++) {
            float xDistance = wells[i].positionX - currentParticle.positionX;
            float yDistance = wells[i].positionY - currentParticle.positionY;
            float zDistance = wells[i].positionZ - currentParticle.positionZ;

            float minimumDistance = 1.0f;
            float distanceSquared = xDistance * xDistance + yDistance * yDistance + zDistance * zDistance + minimumDistance;
            float inverseDistance = rsqrtf(distanceSquared);

            float G = 6.67e-11f;
            float gravitationalAccelerationScalar = G * wells[i].mass / (distanceSquared);

            accelX += gravitationalAccelerationScalar * xDistance * inverseDistance;
            accelY += gravitationalAccelerationScalar * yDistance * inverseDistance;
            accelZ += gravitationalAccelerationScalar * zDistance * inverseDistance;
        }

        currentParticle.velocityX = currentParticle.velocityX + accelX * timeInterval;
        currentParticle.velocityY = currentParticle.velocityY + accelY * timeInterval;
        currentParticle.velocityZ = currentParticle.velocityZ + accelZ * timeInterval;


        float absoluteVelocitySquared = (particles[index].velocityX * particles[index].velocityX) +
            (particles[index].velocityY * particles[index].velocityY) + (particles[index].velocityZ * particles[index].velocityZ);
        float normalizedVelocity = -500 /(absoluteVelocitySquared + 500) + 1;
        uint8_t red = static_cast<uint8_t> (normalizedVelocity * normalizedVelocity* normalizedVelocity * 255);
        uint8_t green = static_cast<uint8_t> ((-8 * (normalizedVelocity-.5) * (normalizedVelocity-.5) + 1)  * 255);
        uint8_t blue = static_cast<uint8_t> (1/( 8* normalizedVelocity + 1) * 200 + 55);
        uint8_t intensity;
        if (particles[index].positionZ < totalDepth && particles[index].positionZ >=0) {
            intensity = static_cast<uint8_t>((totalDepth - particles[index].positionZ)/static_cast<float>(totalDepth) * 0xFF);
        } else {
            intensity = 0x00; 
        }
        particles[index].color = (intensity << 24) | (red << 16) | (green << 8) | blue;


    }
};
