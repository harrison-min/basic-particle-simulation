#pragma once
#include "particle.hpp"
#include <vector>
#include "renderer.hpp"
#include "gravity.hpp"
#include <thrust/device_vector.h>

class Simulation {
    public:
        Simulation(Renderer& newRend, GravityField& newGrav);
        void addParticle (float posX, float posY, float velX, float velY);
        void runSimulation(float timeInterval, int intervals);  
        thrust::device_vector<Particle> particles;

    private:
        Renderer & renderer;
        void updateParticles(float timeInterval);
        GravityField& gravity;
};