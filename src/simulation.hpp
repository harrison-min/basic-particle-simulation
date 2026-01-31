#pragma once
#include "particle.hpp"
#include <vector>
#include "renderer.hpp"
#include "gravity.hpp"
#include <thrust/device_vector.h>

class Simulation {
    public:
        Simulation(Renderer& newRend, GravityField& newGrav);
        void setParticles(const std::vector<Particle> & cpuParticles);
        void runSimulation(float timeInterval, int intervals);  
        thrust::device_vector<Particle> particles;

    private:
        Renderer & renderer;
        void updateParticles(float timeInterval);
        GravityField& gravity;
};